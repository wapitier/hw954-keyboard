/* Receiver-only diagnostics. No HID payloads or macro text logged. */
#include <errno.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/atomic.h>
#include <zephyr/init.h>
#include <zephyr/logging/log.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/sys/byteorder.h>
#include <zmk/usb.h>
#include <zmk/event_manager.h>
#include <zmk/events/position_state_changed.h>
#include <zmk/events/split_peripheral_status_changed.h>
LOG_MODULE_REGISTER(hw954_diag, LOG_LEVEL_INF);
static struct k_work_q diag_queue;
K_THREAD_STACK_DEFINE(diag_stack, 2048);
static struct k_work_delayable poll_work;
static atomic_t keys;
static bool central(struct bt_conn *conn) {
    struct bt_conn_info info;
    return !bt_conn_get_info(conn, &info) && info.type == BT_CONN_TYPE_LE && info.role == BT_CONN_ROLE_CENTRAL;
}
static void connected(struct bt_conn *conn, uint8_t err) {
    if (central(conn)) LOG_INF("RFMON|event=CONNECT|t=%lld|err=%u", k_uptime_get(), err);
}
static void disconnected(struct bt_conn *conn, uint8_t reason) {
    if (central(conn)) LOG_INF("RFMON|event=DISCONNECT|t=%lld|reason=%u", k_uptime_get(), reason);
}
static void security(struct bt_conn *conn, bt_security_t level, enum bt_security_err err) {
    if (central(conn)) LOG_INF("RFMON|event=SECURITY|t=%lld|level=%u|err=%u", k_uptime_get(), level, err);
}
BT_CONN_CB_DEFINE(diag_callbacks) = {.connected=connected, .disconnected=disconnected, .security_changed=security};
static void sample(struct bt_conn *conn, void *data) {
    struct bt_conn_info info;
    if (bt_conn_get_info(conn,&info) || info.type != BT_CONN_TYPE_LE || info.role != BT_CONN_ROLE_CENTRAL || info.state != BT_CONN_STATE_CONNECTED) return;
    (*(int *)data)++;
    uint16_t handle;
    int err=bt_hci_get_conn_handle(conn,&handle);
    struct net_buf *rsp=NULL, *cmd=NULL;
    if (!err) {
        cmd=bt_hci_cmd_create(BT_HCI_OP_READ_RSSI,sizeof(struct bt_hci_cp_read_rssi));
        if (!cmd) err=-ENOMEM;
    }
    if (!err) {
        struct bt_hci_cp_read_rssi *cp=net_buf_add(cmd,sizeof(*cp));
        cp->handle=sys_cpu_to_le16(handle);
        err=bt_hci_cmd_send_sync(BT_HCI_OP_READ_RSSI,cmd,&rsp);
    }
    if (!err && rsp && rsp->len >= sizeof(struct bt_hci_rp_read_rssi)) {
        struct bt_hci_rp_read_rssi *rp=(void *)rsp->data;
        if (!rp->status && rp->rssi != 127) {
            LOG_INF("RFMON|event=RSSI|t=%lld|dbm=%d|interval=%u|latency=%u|timeout=%u",k_uptime_get(),rp->rssi,info.le.interval,info.le.latency,info.le.timeout);
        } else LOG_INF("RFMON|event=RSSI_ERROR|t=%lld|status=%u",k_uptime_get(),rp->status);
    } else LOG_INF("RFMON|event=RSSI_ERROR|t=%lld|err=%d",k_uptime_get(),err);
    if (rsp) net_buf_unref(rsp);
}
static void poll(struct k_work *work) {
    int links=0;
    LOG_INF("RFMON|event=ALIVE|t=%lld|hid=%d|keys=%ld",k_uptime_get(),zmk_usb_is_hid_ready(),(long)atomic_get(&keys));
    bt_conn_foreach(BT_CONN_TYPE_LE,sample,&links);
    LOG_INF("RFMON|event=LINKS|t=%lld|count=%d",k_uptime_get(),links);
    k_work_schedule_for_queue(&diag_queue,&poll_work,K_SECONDS(1));
}
static int listener(const zmk_event_t *eh) {
    const struct zmk_position_state_changed *p=as_zmk_position_state_changed(eh);
    if (p) {
        atomic_inc(&keys);
        LOG_INF("RFMON|event=KEY|t=%lld|pos=%u|down=%d|source=%u",k_uptime_get(),p->position,p->state,p->source);
    }
    const struct zmk_split_peripheral_status_changed *s=as_zmk_split_peripheral_status_changed(eh);
    if (s) LOG_INF("RFMON|event=SPLIT|t=%lld|connected=%d",k_uptime_get(),s->connected);
    return ZMK_EV_EVENT_BUBBLE;
}
ZMK_LISTENER(hw954_diag,listener);
ZMK_SUBSCRIPTION(hw954_diag,zmk_position_state_changed);
ZMK_SUBSCRIPTION(hw954_diag,zmk_split_peripheral_status_changed);
static int init_diag(void) {
    k_work_queue_start(&diag_queue,diag_stack,K_THREAD_STACK_SIZEOF(diag_stack),10,NULL);
    k_work_init_delayable(&poll_work,poll);
    k_work_schedule_for_queue(&diag_queue,&poll_work,K_SECONDS(3));
    return 0;
}
SYS_INIT(init_diag,APPLICATION,99);
