# 第三步：无日志无线 F15

保留已验证的单键无线结构、P0.08接地触发和ZMK v0.3.0。
关闭两端USB日志和普通日志；接收器映射改为F15。
两端都刷入本次固件以移除之前诊断功能，不清除现有配对。
- B刷B-sender-clean.uf2
- A刷A-receiver-F15.uf2
文件包不是UF2；尚未云端编译和实物验证。
上传本目录内部的.github、boards、config、zephyr、build.yaml、README.md。
旧hw954_test文件可保留，其不在当前构建清单中。
此阶段使用USB供电，保持深度休眠关闭，非最终电池功耗配置。
以后仅修改AutoHotkey脚本即可改变F15的电脑端功能。
