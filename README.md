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
  <b><a href="#-magic-glove-english">English</a> | <a href="#-magic-glove-中文版">中文版</a></b>
</p>

---

<h2 id="-magic-glove-english">🇬🇧 English Version</h2>

### 📖 Overview

**Magic Glove** is a wearable gesture controller that transforms a cotton glove into a wireless BLE mouse and keyboard. Built on the Seeed Studio XIAO ESP32-S3 with an MPU-6050 IMU, it supports 3 switchable control modes — from gaming (WASD) to air-mouse gyroscope control — all through intuitive finger-touch gestures.

> 🏆 **Winner of Best Automation & Productivity** at Rutgers IEEE 2026 Build_a_thon 24h competition

### 🛠️ Tech Stack

| Layer | Technology | Details |
|-------|-----------|---------|
| **MCU** | [Seeed Studio XIAO ESP32-S3](https://www.seeedstudio.com/XIAO-ESP32S3-p-5627.html) | ESP32-S3R8, Xtensa LX7 dual-core @ 240 MHz, 8 MB PSRAM |
| **IMU** | [MPU-6050](https://invensense.tdk.com/products/motion-tracking/6-axis/mpu-6050/) | Raw I2C driver (no library) · ±1000°/s gyroscope · 44 Hz DLPF |
| **BLE Stack** | [NimBLE-Arduino](https://github.com/h2zero/NimBLE-Arduino) | Composite HID: Keyboard + Mouse over BLE 5.0 |
| **Touch Sensing** | ESP32-S3 Capacitive Touch | 4-channel with adaptive baseline calibration & debounce |
| **Audio Feedback** | Passive Buzzer | Pattern-based alerts: boot, mode switch, connection events |
| **Framework** | [PlatformIO](https://platformio.org/) | Espressif32 platform · USB CDC debug logging |

### 📐 Hardware Pinout (XIAO ESP32-S3)

![XIAO ESP32-S3 Pinout](https://files.seeedstudio.com/wiki/SeeedStudio-XIAO-ESP32S3/img/xiao-esp32s3-pinout.png)

### 🏗️ Architecture

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

### 🎮 Control Modes

Switch between modes with the **D10 button**. The buzzer beeps to confirm (1/2/3 beeps).

#### Mode 0 — WASD + Space (Gaming)

| Gesture | Action |
|---------|--------|
| Index finger | `W` (Forward) |
| Middle finger | `S` (Backward) |
| Ring finger | `A` (Left) |
| Pinky finger | `D` (Right) |
| All four fingers | `Space` (Jump) |
| Index + Middle | Left Click |
| Ring + Pinky | Right Click |

#### Mode 1 — KL (Rhythm Games)

| Gesture | Action |
|---------|--------|
| Index finger | `K` |
| Middle finger | `L` |
| All four fingers | `Space` |
| Index + Middle | Left Click |
| Ring + Pinky | Right Click |

#### Mode 2 — Gyro Air-Mouse

| Gesture | Action |
|---------|--------|
| Tilt hand | Move cursor (quadratic acceleration) |
| Index finger | Left Click |
| Middle finger | Right Click |
| Index + Middle | Left Click |
| Ring + Pinky | Right Click |

### 🔧 Hardware BOM

| Qty | Component | Purpose |
|-----|-----------|---------|
| 1 | [Seeed Studio XIAO ESP32-S3](https://www.seeedstudio.com/XIAO-ESP32S3-p-5627.html) | Main controller |
| 1 | MPU-6050 module (GY-521) | 6-axis IMU for air-mouse |
| 1 | MH-FMD passive buzzer | Audio feedback |
| 1 | Tactile push button | Mode switching |
| 4 | Copper tape pads | Finger touch sensors |
| 1 | Cotton glove | Wearable base |
| 1 | 3.7V Li-ion battery | Wireless power |

### ⚡ Wiring

| XIAO Pin | GPIO | Function |
|----------|------|----------|
| D0–D3 | GPIO 1–4 | Capacitive touch sensors |
| D4 | GPIO 5 | MPU-6050 SDA (I2C) |
| D5 | GPIO 6 | MPU-6050 SCL (I2C) |
| D8 | GPIO 7 | Buzzer output |
| D10 | GPIO 9 | Mode switch button |

---

<h2 id="-magic-glove-中文版">🇨🇳 中文版</h2>

### 📖 概述

**Magic Glove** 是一款可穿戴手势控制器，将普通棉手套改造为无线 BLE 鼠标与键盘。基于 Seeed Studio XIAO ESP32-S3 和 MPU-6050 惯性测量单元，支持 3 种可切换控制模式——从游戏（WASD 方向键）到空中鼠标陀螺仪控制——全部通过直觉式手指触摸手势完成。

> 🏆 **荣获 Rutgers IEEE 2026 建造马拉松 最佳自动化与生产力奖（Best Automation & Productivity）**

### 🛠️ 技术栈

| 层级 | 技术 | 详情 |
|------|------|------|
| **主控芯片** | [Seeed Studio XIAO ESP32-S3](https://www.seeedstudio.com/XIAO-ESP32S3-p-5627.html) | ESP32-S3R8, Xtensa LX7 双核 @ 240 MHz, 8 MB PSRAM |
| **惯性传感器** | [MPU-6050](https://invensense.tdk.com/products/motion-tracking/6-axis/mpu-6050/) | 原生 I2C 驱动（无第三方库） |
| **蓝牙协议栈** | [NimBLE-Arduino](https://github.com/h2zero/NimBLE-Arduino) | 复合 HID 设备：键盘 + 鼠标，BLE 5.0 |
| **开发框架** | [PlatformIO](https://platformio.org/) | Espressif32 平台 · USB CDC 调试日志 |

### 📐 硬件引脚图 (XIAO ESP32-S3)

![XIAO ESP32-S3 Pinout](https://files.seeedstudio.com/wiki/SeeedStudio-XIAO-ESP32S3/img/xiao-esp32s3-pinout.png)

### 🎮 控制模式

通过 **D10 按钮** 切换模式，蜂鸣器响声确认（1/2/3 声）。

#### 模式 0 — WASD + 空格（游戏）

| 手势 | 动作 |
|------|------|
| 食指触摸 | `W`（前进） |
| 中指触摸 | `S`（后退） |
| 无名指触摸 | `A`（左移） |
| 小指触摸 | `D`（右移） |
| 四指同时触摸 | `空格`（跳跃） |

#### 模式 2 — 陀螺仪空中鼠标

| 手势 | 动作 |
|------|------|
| 倾斜手掌 | 移动光标（二次加速度算法） |
| 食指触摸 | 鼠标左键 |
| 中指触摸 | 鼠标右键 |

### 🚀 快速开始

```bash
git clone https://github.com/LucasYanzy/Magic-Glove.git
cd Magic-Glove
# 在 VS Code 中打开（需安装 PlatformIO 扩展）
```

---

## 📂 Project Structure

```
Magic-Glove/
├── src/                    # Firmware source code
├── docs/                   # Documentation
├── platformio.ini          # Build configuration
└── README.md               # This file
```

## 📄 License

MIT License — see [LICENSE](LICENSE) for details.

