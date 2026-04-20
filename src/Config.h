/**
 * @file Config.h
 * @brief Hardware configuration and pins for Magic Glove | 硬件配置与引脚定义
 * @author LucasYanzy
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ==================== Pin Definitions (XIAO ESP32-S3) | 引脚定义 ====================
namespace Pins {
    const int TOUCH_PINS[] = {1, 2, 3, 4}; // D0(Index), D1(Middle), D2(Ring), D3(Pinky)
    const int I2C_SDA      = 5;            // D4 for MPU-6050 SDA
    const int I2C_SCL      = 6;            // D5 for MPU-6050 SCL
    const int BUZZER       = 7;            // D8 (Avoids D6/D7 Serial pins)
    const int MODE_BUTTON  = 9;            // D10 for mode switching
    const int LED          = LED_BUILTIN;  // Typically GPIO 21
}

// ==================== MPU-6050 Settings | 陀螺仪设置 ====================
namespace MPU_Config {
    const uint8_t ADDR         = 0x68; // I2C address of MPU-6050
    const float GYRO_DEADZONE  = 15.0; // Noise threshold
    const int MOUSE_MAX_SPEED  = 100;  // Max cursor speed
    // Factors for non-linear acceleration mapping | 二次加速度映射因子
    const float FACTOR_X       = 0.005;
    const float FACTOR_Y       = 0.005;
}

// ==================== Timing | 时间与防抖 ====================
const unsigned long DEBOUNCE_MS = 250;      // Mode button debounce (ms)
const unsigned long LOOP_PERIOD_MS = 10;    // Main loop period (10ms = 100Hz)

#endif
