#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ==================== Pin Definitions (XIAO ESP32-S3) ====================
namespace Pins {
    const int TOUCH_PINS[] = {1, 2, 3, 4}; // D0, D1, D2, D3
    const int I2C_SDA      = 5;            // D4
    const int I2C_SCL      = 6;            // D5
    const int BUZZER       = 7;            // D8 (Safe: avoids D6/D7 Serial pins)
    const int MODE_BUTTON  = 9;            // D10
    const int LED          = LED_BUILTIN;  // Typically GPIO 21
}

// ==================== MPU-6050 Settings ====================
namespace MPU_Config {
    const uint8_t ADDR         = 0x68;
    const float GYRO_DEADZONE  = 15.0;
    const int MOUSE_MAX_SPEED  = 100;
    const float FACTOR_X       = 0.005;
    const float FACTOR_Y       = 0.005;
}

// ==================== Timing ====================
const unsigned long DEBOUNCE_MS = 250;
const unsigned long LOOP_PERIOD_MS = 10; // 100Hz

#endif
