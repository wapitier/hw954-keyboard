# HW-954 第二步：单键无线实验

沿用已成功编译的 ZMK v0.3.0 和 nice_nano_v2 目标。
此包是配置源文件，不是 UF2。尚未进行云端编译和实物验证。

## 角色与接线

- B 板：sender，按钮保持 P0.08（008）与 GND，USB 仅供电；已禁用 USB HID。
- A 板：receiver，无需外部接线，USB 接电脑；检查排针不存在短路。
- 两板之间不接电线。无需在 Windows 蓝牙设置中配对。
- 当前关闭深度休眠用于排错，不用于测量最终电池续航。

## 上传

上传本文件夹内部的 .github、boards、config、zephyr、build.yaml、README.md
到现有 GitHub 仓库根目录。旧 hw954_test 文件保留不影响本次构建。
不要多套一层 hw954-step2 目录。等待 Actions 全部成功，下载最新 firmware。
应得到含 hw954_sender、hw954_receiver、settings_reset 的三份 UF2。

## 刷写顺序

1. B 进入引导模式，刷 settings_reset，自动重启后等待至少 5 秒，再断电。
2. A 进入引导模式，刷相同 settings_reset，自动重启后等待至少 5 秒，再断电。
3. B 再进引导模式，刷 hw954_sender；完成后断电。
4. A 再进引导模式，刷 hw954_receiver；完成后断电。
5. 插入 A 和 B 的 USB，放在相距 20-50cm 处，等待约 10-30 秒再测试。

每次只复制一份 UF2。清设置不更新 Bootloader；它清除已有 ZMK 配对和偏好。
刷 reset 后没有键盘输入是正常的，需要重新双击 RST-GND 进入引导模式。
不要在完成所有刷写步骤后又刷回 reset。

## 测试

英文输入，记事本获得焦点，按 B 的按钮，应输入 a。
拔掉 A 的 USB，B 保持供电，再按按钮应不再有输入。
松开按钮，重新插入 A，等待连接后再次按下应输入 a。
若失败记录具体文件名和现象，不要随机刷其他型号固件。
