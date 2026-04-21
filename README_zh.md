<p align="center">
  <img src="https://img.shields.io/badge/🏆_最佳自动化与生产力奖-Rutgers_IEEE_2026_Build_a_thon-gold?style=for-the-badge" alt="奖项"/>
</p>

<h1 align="center">🧤 Magic Glove</h1>

<p align="center">
  <strong>可穿戴 BLE 手势控制器 —— 将你的手变为无线鼠标和键盘</strong>
</p>

<p align="center">
  <a href="https://wiki.seeedstudio.com/xiao_esp32s3_getting_started/">
    <img src="https://img.shields.io/badge/ESP32--S3-固件-blue?style=flat-square&logo=espressif" alt="ESP32-S3"/>
  </a>
  <a href="https://github.com/h2zero/NimBLE-Arduino">
    <img src="https://img.shields.io/badge/BLE_HID-鼠标_+_键盘-blueviolet?style=flat-square&logo=bluetooth" alt="BLE HID"/>
  </a>
  <a href="https://platformio.org/">
    <img src="https://img.shields.io/badge/PlatformIO-构建系统-orange?style=flat-square&logo=platformio" alt="PlatformIO"/>
  </a>
  <a href="LICENSE">
    <img src="https://img.shields.io/badge/License-MIT-green?style=flat-square" alt="MIT License"/>
  </a>
</p>

<p align="center">
  <a href="https://canva.link/y9bu67ktrjb0xm3">
    <img src="https://img.shields.io/badge/Canva-演示文稿_Slide-00C4CC?style=for-the-badge&logo=canva&logoColor=white" alt="View Presentation"/>
  </a>
</p>

<p align="center">
  <b><a href="README.md">English</a> | 中文版</b>
</p>

---

## 📖 概述

**Magic Glove** 是一款可穿戴手势控制器，将普通棉手套改造为无线 BLE 鼠标与键盘。基于 Seeed Studio XIAO ESP32-S3 和 MPU-6050 惯性测量单元，支持 3 种可切换控制模式——从游戏（WASD 方向键）到空中鼠标陀螺仪控制——全部通过直觉式手指触摸手势完成。

> 🏆 **荣获 Rutgers IEEE 2026 建造马拉松 最佳自动化与生产力奖（Best Automation & Productivity）**

## 🛠️ 技术栈

| 层级 | 技术 | 详情 |
|------|------|------|
| **主控芯片** | [Seeed Studio XIAO ESP32-S3](https://www.seeedstudio.com/XIAO-ESP32S3-p-5627.html) | ESP32-S3R8, Xtensa LX7 双核 @ 240 MHz, 8 MB PSRAM |
| **惯性传感器** | [MPU-6050](https://invensense.tdk.com/products/motion-tracking/6-axis/mpu-6050/) | 原生 I2C 驱动（无第三方库）· ±1000°/s 陀螺仪 · 44 Hz 数字低通滤波 |
| **蓝牙协议栈** | [NimBLE-Arduino](https://github.com/h2zero/NimBLE-Arduino) + ESP32-NimBLE-Combo | 复合 HID 设备：键盘 + 鼠标，BLE 5.0 |
| **触摸感应** | ESP32-S3 电容触摸 | 4 通道自适应基线校准 + 防抖 |
| **声音反馈** | MH-FMD 无源蜂鸣器 | 按模式反馈：启动音、模式切换音、连接状态音 |
| **开发框架** | Arduino ([PlatformIO](https://platformio.org/)) | Espressif32 平台 · USB CDC 调试日志 |
| **运动算法** | 自定义二次加速度算法 | 非线性光标映射：`speed = sign(ω) × ω² × factor` |

## 📐 硬件引脚图 (XIAO ESP32-S3)

<p align="center">
  <img src="https://files.seeedstudio.com/wiki/SeeedStudio-XIAO-ESP32S3/img/xiao-esp32s3-pinout.png" alt="XIAO ESP32-S3 引脚图" width="800">
</p>

## 🏗️ 架构

```
src/
├── main.cpp            # 程序入口 · setup/loop · MPU-6050 原生 I2C 驱动
├── Config.h            # 引脚定义 · MPU 参数 · 时序常量
├── BLEManager.h/.cpp   # BLE HID 复合设备（NimBLE 键盘 + 鼠标）
├── TouchSensor.h/.cpp  # 4 通道电容触摸，自适应校准
├── ActionMapper.h/.cpp # 手势 → 动作映射引擎（3 种模式）
├── Buzzer.h/.cpp       # 声音反馈（启动 / 模式切换 / 连接状态）
└── USBHIDManager.h/.cpp# USB HID 备用驱动（开发调试用）
```

## 🎮 控制模式

通过 **D10 按钮** 切换模式，蜂鸣器响声确认（1/2/3 声）。

### 模式 0 — WASD + 空格（游戏）

| 手势 | 动作 |
|------|------|
| 食指触摸 | `W`（前进） |
| 中指触摸 | `S`（后退） |
| 无名指触摸 | `A`（左移） |
| 小指触摸 | `D`（右移） |
| 四指同时触摸 | `空格`（跳跃） |
| 食指 + 中指 | 鼠标左键 |
| 无名指 + 小指 | 鼠标右键 |

### 模式 1 — KL（音游模式）

| 手势 | 动作 |
|------|------|
| 食指触摸 | `K` |
| 中指触摸 | `L` |
| 四指同时触摸 | `空格` |
| 食指 + 中指 | 鼠标左键 |
| 无名指 + 小指 | 鼠标右键 |

### 模式 2 — 陀螺仪空中鼠标

| 手势 | 动作 |
|------|------|
| 倾斜手掌 | 移动光标（二次加速度算法） |
| 食指触摸 | 鼠标左键 |
| 中指触摸 | 鼠标右键 |
| 食指 + 中指 | 鼠标左键 |
| 无名指 + 小指 | 鼠标右键 |

## 🔧 硬件清单

| 数量 | 元件 | 用途 |
|------|------|------|
| 1 | [Seeed Studio XIAO ESP32-S3](https://www.seeedstudio.com/XIAO-ESP32S3-p-5627.html) | 主控制器 |
| 1 | [MPU-6050 模块 (GY-521)](https://invensense.tdk.com/products/motion-tracking/6-axis/mpu-6050/) | 6 轴惯性传感器，空中鼠标 |
| 1 | MH-FMD 无源蜂鸣器 | 声音反馈 |
| 1 | 轻触按钮 | 模式切换 |
| 4 | 铜箔贴片 | 手指触摸传感器（食指/中指/无名指/小指） |
| 2 | 铜箔贴片 | 接地触摸面（拇指 + 掌心） |
| 1 | 棉手套 | 可穿戴载体 |
| 1 | 3.7V 锂离子电池 | 无线供电 |
| — | 柔性硅胶导线 | 连接用 |

## ⚡ 接线

详见 [docs/wiring.md](docs/wiring.md) 完整引脚接线表。

| XIAO 引脚 | GPIO | 功能 |
|-----------|------|------|
| D0–D3 | GPIO 1–4 | 电容触摸传感器 |
| D4 | GPIO 5 | MPU-6050 SDA (I2C) |
| D5 | GPIO 6 | MPU-6050 SCL (I2C) |
| D8 | GPIO 7 | 蜂鸣器输出 |
| D10 | GPIO 9 | 模式切换按钮 |

## 🚀 快速开始

### PlatformIO（推荐）

```bash
git clone https://github.com/LucasYanzy/Magic-Glove.git
cd Magic-Glove
# 在 VS Code 中打开（需安装 PlatformIO 扩展），然后：
# Build → Upload → Monitor
```

### Arduino IDE

1. 安装 [ESP32 Arduino Core](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html)
2. 通过库管理器安装：
   - `NimBLE-Arduino` by h2zero
   - `ESP32-NimBLE-Combo` by A-box1000
3. 选择开发板：**XIAO ESP32S3**
4. 上传

## 🎯 校准

1. 给设备上电
2. LED 快速闪烁 — **请勿触摸任何手指触摸片**
3. 约 1 秒后 LED 常亮 → 校准完成
4. 切换到陀螺仪模式时，保持手部静止以自动校准陀螺仪

## 📂 项目结构

```
Magic-Glove/
├── src/                    # 固件源码
│   ├── main.cpp            # 主程序入口 + MPU-6050 驱动
│   ├── Config.h            # 硬件配置
│   ├── BLEManager.h/.cpp   # BLE HID 蓝牙管理
│   ├── TouchSensor.h/.cpp  # 电容触控引擎
│   ├── ActionMapper.h/.cpp # 手势映射管理
│   ├── Buzzer.h/.cpp       # 声音反馈管理
│   └── USBHIDManager.h/.cpp# USB HID 调试接口
├── docs/
│   └── wiring.md           # 接线指南
├── platformio.ini          # PlatformIO 编译配置
├── library.json            # 项目库元数据
├── LICENSE                 # MIT 许可证
└── README.md               # 本文件
```

## 📄 许可证

MIT License — 详见 [LICENSE](LICENSE)。
