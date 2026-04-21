<p align="center">
  <img src="https://img.shields.io/badge/🏆_Best_Automation_&_Productivity-Rutgers_IEEE_2026_Build_a_thon-gold?style=for-the-badge" alt="Award Badge"/>
</p>

<h1 align="center">🧤 Magic Glove</h1>

<p align="center">
  <strong>Wearable BLE Gesture Controller — Turn your hand into a wireless mouse & keyboard</strong>
</p>

<p align="center">
  <a href="https://wiki.seeedstudio.com/xiao_esp32s3_getting_started/">
    <img src="https://img.shields.io/badge/ESP32--S3-Firmware-blue?style=flat-square&logo=espressif" alt="ESP32-S3"/>
  </a>
  <a href="https://github.com/h2zero/NimBLE-Arduino">
    <img src="https://img.shields.io/badge/BLE_HID-Mouse_+_Keyboard-blueviolet?style=flat-square&logo=bluetooth" alt="BLE HID"/>
  </a>
  <a href="https://platformio.org/">
    <img src="https://img.shields.io/badge/PlatformIO-Build_System-orange?style=flat-square&logo=platformio" alt="PlatformIO"/>
  </a>
  <a href="LICENSE">
    <img src="https://img.shields.io/badge/License-MIT-green?style=flat-square" alt="MIT License"/>
  </a>
</p>

<p align="center">
  <a href="https://canva.link/y9bu67ktrjb0xm3">
    <img src="https://img.shields.io/badge/Canva-View_Presentation-00C4CC?style=for-the-badge&logo=canva&logoColor=white" alt="View Presentation"/>
  </a>
</p>

<p align="center">
  <b>English | <a href="README_zh.md">中文版</a></b>
</p>

---

## 📖 Overview

**Magic Glove** is a wearable gesture controller that transforms a cotton glove into a wireless BLE mouse and keyboard. Built on the Seeed Studio XIAO ESP32-S3 with an MPU-6050 IMU, it supports 3 switchable control modes — from gaming (WASD) to air-mouse gyroscope control — all through intuitive finger-touch gestures.

> 🏆 **Winner of Best Automation & Productivity** at Rutgers IEEE 2026 Build_a_thon 24h competition

## 🛠️ Tech Stack

| Layer | Technology | Details |
|-------|-----------|---------|
| **MCU** | [Seeed Studio XIAO ESP32-S3](https://www.seeedstudio.com/XIAO-ESP32S3-p-5627.html) | ESP32-S3R8, Xtensa LX7 dual-core @ 240 MHz, 8 MB PSRAM |
| **IMU** | [MPU-6050](https://invensense.tdk.com/products/motion-tracking/6-axis/mpu-6050/) | Raw I2C driver (no library) · ±1000°/s gyroscope · 44 Hz DLPF |
| **BLE Stack** | [NimBLE-Arduino](https://github.com/h2zero/NimBLE-Arduino) + ESP32-NimBLE-Combo | Composite HID: Keyboard + Mouse over BLE 5.0 |
| **Touch Sensing** | ESP32-S3 Capacitive Touch | 4-channel with adaptive baseline calibration & debounce |
| **Audio Feedback** | MH-FMD Passive Buzzer | Pattern-based alerts: boot, mode switch, connection events |
| **Framework** | Arduino ([PlatformIO](https://platformio.org/)) | Espressif32 platform · USB CDC debug logging |
| **Motion Algorithm** | Custom Quadratic Acceleration | Non-linear cursor mapping: `speed = sign(ω) × ω² × factor` |

## 📐 Hardware Pinout (XIAO ESP32-S3)

<p align="center">
  <img src="https://files.seeedstudio.com/wiki/SeeedStudio-XIAO-ESP32S3/img/xiao-esp32s3-pinout.png" alt="XIAO ESP32-S3 Pinout" width="800">
</p>

## 🏗️ Architecture

```
src/
├── main.cpp            # Application entry · setup/loop · MPU-6050 raw I2C driver
├── Config.h            # Pin definitions · MPU parameters · timing constants
├── BLEManager.h/.cpp   # BLE HID composite device (NimBLE Keyboard + Mouse)
├── TouchSensor.h/.cpp  # 4-channel capacitive touch with adaptive calibration
├── ActionMapper.h/.cpp # Gesture → action mapping engine (3 modes)
├── Buzzer.h/.cpp       # Audio feedback patterns (boot / mode / connection)
└── USBHIDManager.h/.cpp# USB HID fallback driver (development/debug)
```

## 🎮 Control Modes

Switch between modes with the **D10 button**. The buzzer beeps to confirm (1/2/3 beeps).

### Mode 0 — WASD + Space (Gaming)

| Gesture | Action |
|---------|--------|
| Index finger | `W` (Forward) |
| Middle finger | `S` (Backward) |
| Ring finger | `A` (Left) |
| Pinky finger | `D` (Right) |
| All four fingers | `Space` (Jump) |
| Index + Middle | Left Click |
| Ring + Pinky | Right Click |

### Mode 1 — KL (Rhythm Games)

| Gesture | Action |
|---------|--------|
| Index finger | `K` |
| Middle finger | `L` |
| All four fingers | `Space` |
| Index + Middle | Left Click |
| Ring + Pinky | Right Click |

### Mode 2 — Gyro Air-Mouse

| Gesture | Action |
|---------|--------|
| Tilt hand | Move cursor (quadratic acceleration) |
| Index finger | Left Click |
| Middle finger | Right Click |
| Index + Middle | Left Click |
| Ring + Pinky | Right Click |

## 🔧 Hardware BOM

| Qty | Component | Purpose |
|-----|-----------|---------|
| 1 | [Seeed Studio XIAO ESP32-S3](https://www.seeedstudio.com/XIAO-ESP32S3-p-5627.html) | Main controller |
| 1 | [MPU-6050 module (GY-521)](https://invensense.tdk.com/products/motion-tracking/6-axis/mpu-6050/) | 6-axis IMU for air-mouse |
| 1 | MH-FMD passive buzzer | Audio feedback |
| 1 | Tactile push button | Mode switching |
| 4 | Copper tape pads | Finger touch sensors (Index/Middle/Ring/Pinky) |
| 2 | Copper tape pads | Ground plane (Thumb + Palm) |
| 1 | Cotton glove | Wearable base |
| 1 | 3.7V Li-ion battery | Wireless power |
| — | Flexible silicone wire | Connections |

## ⚡ Wiring

See [docs/wiring.md](docs/wiring.md) for the full pin connection table.

| XIAO Pin | GPIO | Function |
|----------|------|----------|
| D0–D3 | GPIO 1–4 | Capacitive touch sensors |
| D4 | GPIO 5 | MPU-6050 SDA (I2C) |
| D5 | GPIO 6 | MPU-6050 SCL (I2C) |
| D8 | GPIO 7 | Buzzer output |
| D10 | GPIO 9 | Mode switch button |

## 🚀 Quick Start

### PlatformIO (Recommended)

```bash
git clone https://github.com/LucasYanzy/Magic-Glove.git
cd Magic-Glove
# Open in VS Code with PlatformIO extension, then:
# Build → Upload → Monitor
```

### Arduino IDE

1. Install [ESP32 Arduino Core](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html)
2. Install libraries via Library Manager:
   - `NimBLE-Arduino` by h2zero
   - `ESP32-NimBLE-Combo` by A-box1000
3. Select board: **XIAO ESP32S3**
4. Upload

## 🎯 Calibration

1. Power on the device
2. LED blinks rapidly — **do NOT touch any finger pads**
3. After ~1 second, LED stays solid → calibration complete
4. When switching to Gyro mode, keep hand still for auto gyro calibration

## 📂 Project Structure

```
Magic-Glove/
├── src/                    # Firmware source code
│   ├── main.cpp            # Entry point + MPU-6050 driver
│   ├── Config.h            # Hardware configuration
│   ├── BLEManager.h/.cpp   # BLE HID manager
│   ├── TouchSensor.h/.cpp  # Capacitive touch engine
│   ├── ActionMapper.h/.cpp # Gesture mapping
│   ├── Buzzer.h/.cpp       # Audio feedback
│   └── USBHIDManager.h/.cpp# USB HID (debug)
├── docs/
│   └── wiring.md           # Wiring guide
├── platformio.ini          # Build configuration
├── library.json            # Project metadata
├── LICENSE                 # MIT License
└── README.md               # This file
```

## 📄 License

MIT License — see [LICENSE](LICENSE) for details.
