# HW954 17键：2026-10-22最新映射

B为键盘，A为USB接收器。每个常开按钮连接指定GPIO与GND。
精确映射见pin-map.csv。P0.10为关机键，已增加CONFIG_NFCT_PINS_AS_GPIOS=y。
不使用底部P1.01，不连接NFC天线。登录序列仍为SPACE,3,2,6,2，不含回车。
软件A/B/C仍发送F13/F14/F15；关机键发送F16，电脑端AHK判断持续按住3秒。

上传本目录内部.github、boards、config、zephyr、build.yaml、README.md至现有仓库根目录。
最新构建成功后，B刷B-keyboard-17keys-20261022.uf2，A刷A-receiver-17keys-20261022.uf2。
两端都要更新，扫描顺序与按键映射需要配套；通常不需要settings_reset。
AutoHotkey沿用之前的HW954-17keys.ahk；其关机测试开关状态保持原设置。
固件无USB日志；当前仍关闭深度休眠用于USB供电测试，非最终省电配置。
已做GPIO唯一性与17项映射一致性静态检查，尚未云端编译和实物验证。
公开仓库中不要使用真实登录凭据。
