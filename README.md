# HW954 17 independent keys, USB-powered test

B = keyboard; A = receiver. ZMK v0.3.0, nice_nano_v2; no USB logging.
Each normally-open switch connects its assigned GPIO to GND. No VCC or diode.
See pin-map.csv. Key 17 uses the bottom P1.01 / 101 pad, not a side pin.
All 17 entries in both keymaps and the shared transform have matching order.
Login emits exactly SPACE,3,2,6,2, with no Enter.
Shutdown emits F16; AutoHotkey measures the hold and handles shutdown after 3 seconds.
The companion HW954-17keys.ahk is installed on the PC, not on the boards.
It defaults to a shutdown test message. Set SHUTDOWN_TEST_MODE := false for actual shutdown.
Apps A/B default to empty; configure APP_A and APP_B as executable paths.

Upload .github, boards, config, zephyr, build.yaml, README.md to the repository root.
Both boards require flashing this time: B-keyboard-17keys.uf2 and A-receiver-17keys.uf2.
Do not clear pairing merely for this key-count update. Old hw954_test is unused.
No batteries yet; deep sleep stays disabled during testing.
HKRO is retained, so hardware-independent wiring does not imply 17 simultaneous HID keys.
The configuration is statically checked only; not cloud-compiled or hardware-tested here.
Do not put real credentials into public repositories.
