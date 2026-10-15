# HW-954 第一步：单键 USB 测试

本配置使用 ZMK v0.3.0 和 nice_nano_v2 目标，仅用于验证 USB 与一个按键。
已按 ZMK 官方配置结构编写，尚未在云端编译或实物测试；不是可直接刷入的固件。
不更新 Bootloader，不包含密码，不启用蓝牙、电池上报及外部电源控制。

## 接线

断开 USB 后，将一个常开瞬时按钮接在 P0.08 和 GND 之间。
nice!nano 标准布局中 P0.08 对应 Pro Micro 的 0/RX 引脚。
请以实物及商家引脚图的 P0.08 为准，不要按“第0个孔”计数。
本实验不需要二极管或外接电阻。不要连接 BAT、VCC、3V3、5V。

## 通过 GitHub 构建

1. 使用 zmkfirmware/unified-zmk-config-template 模板创建自己的仓库。
2. 把本文件夹的内容上传到仓库根目录；不要多套一层 hw954-step1 文件夹。
3. 保留并上传 .github、boards、config、zephyr 文件夹和 build.yaml。
4. 在 Actions 中等 Build HW954 test firmware 成功；下载 firmware 构建产物并解压。
5. 如果编译失败，不要刷写其他固件；提供失败日志以便修正。

## 刷入与测试

只连接 A 板，进入 NICENANO 引导盘，将构建产物里的测试 .uf2 文件复制进去。
磁盘消失通常表示自动重启；打开记事本、切换英文输入，按按钮应输入 a。
长按可能被 Windows 自动重复成多个 a。这个阶段 B 板不用连接。
双击 RST-GND 仍用于重新进入引导程序。

GitHub 公共仓库中不得写入真实登录密码。
