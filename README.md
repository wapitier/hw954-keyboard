# HW954 USB 日志诊断版

此包在第二阶段配置上仅增加官方 zmk-usb-logging snippet、日志缓冲及8秒启动日志延迟。
没有改变无线参数、引脚或配对设置。尚未云端编译和实物验证。
上传本目录内容到仓库根目录，编译完成后：
- A 板刷 A-receiver-debug.uf2
- B 板刷 B-sender-debug.uf2
本次先不要刷 settings_reset，以保留当前状态用于诊断。
Windows 设备管理器 -> 端口(COM和LPT) 找到每块板新增的COM口。
PuTTY选择Serial，设置对应COM口、115200、Flow control=None。
先连好一块板的串口，再给另一块板通电，等待并按B按钮；保存日志。
如板插入后没有COM口，记录“其他设备”属性中的设备状态、硬件ID及黄色警告。
当前只是诊断版，不用于评估电池续航。
