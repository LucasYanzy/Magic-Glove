# Wiring Guide | 接线指南

This document describes how to connect all components to the Seeed Studio XIAO ESP32-S3 board.
本文档说明如何将所有组件连接到 Seeed Studio XIAO ESP32-S3 开发板。

## 🔌 Pin Connections | 引脚连接表

| XIAO ESP32-S3 Pin | GPIO | Function (功能) | Connected to (连接对象) |
|-------------------|------|-----------------|-------------------------|
| **D0** | GPIO 1 | Touch Sensor 1 (电容触摸) | Index Finger Copper Pad (食指铜箔) |
| **D1** | GPIO 2 | Touch Sensor 2 (电容触摸) | Middle Finger Copper Pad (中指铜箔) |
| **D2** | GPIO 3 | Touch Sensor 3 (电容触摸) | Ring Finger Copper Pad (无名指铜箔) |
| **D3** | GPIO 4 | Touch Sensor 4 (电容触摸) | Pinky Finger Copper Pad (小指铜箔) |
| **D4** | GPIO 5 | I2C SDA (数据线) | MPU-6050 SDA 针脚 |
| **D5** | GPIO 6 | I2C SCL (时钟线) | MPU-6050 SCL 针脚 |
| **D8** | GPIO 7 | Digital Output (数字输出)| MH-FMD Buzzer Signal (蜂鸣器信号端) |
| **D10** | GPIO 9 | Digital Input (数字输入) | Mode Button (模式切换按钮) |
| **GND** | GND | Ground (接地) | Thumb & Palm Copper Pads (拇指与掌心铜箔) |
| **GND** | GND | Ground (接地) | MPU-6050 GND & Buzzer GND & Button GND |
| **5V (VIN)** | 5V | Power Input (电源) | Li-ion Battery '+' (锂电池正极) |
| **3V3** | 3.3V | Power Output (电源) | MPU-6050 VCC 针脚 |
| **GND** | GND | Power Input (电源) | Li-ion Battery '-' (锂电池负极) |

## 🛠️ Assembly Tips | 组装建议

### English
1. Stick the copper pads on the tip of each finger (Index, Middle, Ring, Pinky).
2. Stick one copper pad on the tip of your thumb, and another on the palm of your hand (these act as the common Ground).
3. Run flexible silicone wires from each pad to the XIAO board, securing them to the glove.
4. Mount the MPU-6050 securely on the back of the hand (level when resting).
5. Add a physical switch between the battery positive terminal and the VIN pin for easy power control.
6. Secure the XIAO board and battery to the back of the glove using velcro or a 3D printed case.

### 中文
1. 将铜箔贴片贴在每根手指（食指、中指、无名指、小指）的指尖上。
2. 将一个铜箔贴片贴在拇指指尖，另一个贴在掌心（这两个作为公共接地端）。
3. 使用柔性硅胶导线将每个贴片连接到 XIAO 开发板，并将其固定在手套上。
4. 将 MPU-6050 稳固地安装在手背上（手部自然平放时保持水平）。
5. 在电池正极和 VIN 引脚之间添加一个物理开关，以方便控制电源。
6. 使用魔术贴或 3D 打印外壳将 XIAO 开发板和电池固定在手套背面。
