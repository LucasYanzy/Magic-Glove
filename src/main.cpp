#include <Arduino.h>
#include <Wire.h>
#include <esp_task_wdt.h>
#include "Config.h"
#include "TouchSensor.h"
#include "BLEManager.h"
#include "ActionMapper.h"
#include "Buzzer.h"

// ==================== Hardware Objects ====================
BLEManager ble;
TouchSensor touchSensor(Pins::TOUCH_PINS);
ActionMapper mapper(&ble);
Buzzer buzzer(Pins::BUZZER);

// ==================== State Variables ====================
uint8_t currentMode     = 0;       // 0=WASD+SPC, 1=KL, 2=GYRO
bool    lastButtonState = HIGH;
unsigned long lastDebounce = 0;
bool wasConnected = false;
bool mpuReady = false;
float gyroOffsetX = 0, gyroOffsetZ = 0;

const char* modeNames[] = {"WASD+SPC", "KL", "GYRO"};

// ==================== MPU-6050 I2C Logic ====================

void initMPU6050() {
    Wire.begin(Pins::I2C_SDA, Pins::I2C_SCL);
    Wire.setClock(100000);
    Wire.setTimeOut(100); // Prevent I2C hangs

    // WHO_AM_I check
    Wire.beginTransmission(MPU_Config::ADDR);
    Wire.write(0x75);
    if (Wire.endTransmission(false) != 0) {
        Serial.println("[ERR] MPU-6050 I2C communication failed");
        return;
    }
    
    Wire.requestFrom(MPU_Config::ADDR, (uint8_t)1);
    if (Wire.available()) {
        uint8_t whoAmI = Wire.read();
        Serial.printf("[OK] MPU-6050 detected (ID: 0x%02X)\n", whoAmI);
        mpuReady = true;
    }

    if (mpuReady) {
        // Wake up MPU
        Wire.beginTransmission(MPU_Config::ADDR);
        Wire.write(0x6B); // PWR_MGMT_1
        Wire.write(0x00);
        Wire.endTransmission(true);
        delay(50);

        // Config Gyro Range ±1000°/s
        Wire.beginTransmission(MPU_Config::ADDR);
        Wire.write(0x1B); 
        Wire.write(0x10); 
        Wire.endTransmission(true);

        // DLPF: 44Hz
        Wire.beginTransmission(MPU_Config::ADDR);
        Wire.write(0x1A); 
        Wire.write(0x03); 
        Wire.endTransmission(true);
    }
}

void readGyroXZ(float &gx, float &gz) {
    if (!mpuReady) return;
    Wire.beginTransmission(MPU_Config::ADDR);
    Wire.write(0x43); // GYRO_XOUT_H
    Wire.endTransmission(false);
    
    if (Wire.requestFrom(MPU_Config::ADDR, (uint8_t)6) == 6) {
        int16_t x = (Wire.read() << 8) | Wire.read();
        int16_t y = (Wire.read() << 8) | Wire.read(); // Read but ignore
        int16_t z = (Wire.read() << 8) | Wire.read();
        (void)y;
        
        gx = x / 32.8f;
        gz = z / 32.8f;
    }
}

void calibrateGyro() {
    Serial.println("[CAL] Calibrating Gyro... keep glove still.");
    float sumX = 0, sumZ = 0;
    const int SAMPLES = 50; // Reduced from 100 to avoid WDT timeout
    for (int i = 0; i < SAMPLES; i++) {
        float gx, gz;
        readGyroXZ(gx, gz);
        sumX += gx;
        sumZ += gz;
        delay(5);
        yield(); // Feed the watchdog
    }
    gyroOffsetX = sumX / SAMPLES;
    gyroOffsetZ = sumZ / SAMPLES;
    Serial.printf("[CAL] Finished. Offset X:%.2f Z:%.2f\n", gyroOffsetX, gyroOffsetZ);
}

// ==================== Setup ====================

void setup() {
    // Give the system time to stabilize before doing anything
    delay(500);
    
    Serial.begin(115200);
    delay(100); // Wait for serial to initialize
    Serial.println("\n\n[BOOT] Starting Gesture Mouse Glove...");
    
    pinMode(Pins::MODE_BUTTON, INPUT_PULLUP);
    pinMode(Pins::LED, OUTPUT);
    
    buzzer.begin();
    yield(); // Feed watchdog
    
    // Initializing BLE
    Serial.println("[INIT] BLE starting...");
    ble.begin();
    Serial.println("[OK] BLE: Magic MouseX ready");
    yield(); // Feed watchdog after BLE init

    // Initializing MPU
    Serial.println("[INIT] MPU-6050 starting...");
    initMPU6050();
    yield(); // Feed watchdog
    if (mpuReady) {
        calibrateGyro();
    }
    yield(); // Feed watchdog

    // Initializing Touch
    Serial.println("[INIT] Touch sensors starting...");
    touchSensor.begin();
    Serial.println("[OK] Touch sensors calibrated");
    yield(); // Feed watchdog

    buzzer.bootSuccess();
    Serial.println("--- System Started Successfully ---");
}

// ==================== Loop ====================

void loop() {
    static unsigned long lastUpdate = 0;
    static unsigned long lastLog    = 0;
    static int lastMx = 0, lastMy  = 0;

    bool connected = ble.isConnected();

    // Connection Status Handling
    if (connected != wasConnected) {
        wasConnected = connected;
        buzzer.connectionChanged(connected);
        digitalWrite(Pins::LED, connected ? LOW : HIGH); // LOW is ON for many XIAO LEDs
        Serial.printf("[BLE] State changed: %s\n", connected ? "CONNECTED" : "DISCONNECTED");
    }

    // Mode Switching
    bool btnState = digitalRead(Pins::MODE_BUTTON);
    if (btnState == LOW && lastButtonState == HIGH && (millis() - lastDebounce > DEBOUNCE_MS)) {
        lastDebounce = millis();
        currentMode = (currentMode + 1) % 3;
        ble.releaseAll();
        
        buzzer.modeChanged(currentMode);
        
        if (currentMode == 2 && mpuReady) {
            calibrateGyro();
        }
        Serial.printf("[MODE] Switched to: %s\n", modeNames[currentMode]);
    }
    lastButtonState = btnState;

    // Main Control Loop (100Hz)
    if (millis() - lastUpdate >= LOOP_PERIOD_MS) {
        lastUpdate = millis();

        touchSensor.update();
        uint8_t touchStatus = touchSensor.getTouchState();

        if (connected) {
            switch (currentMode) {
                case 0: // WASD
                case 1: // KL
                    mapper.processAction(touchStatus, currentMode);
                    lastMx = 0; lastMy = 0;
                    break;

                case 2: // GYRO
                    mapper.processAction(touchStatus, currentMode);
                    if (mpuReady) {
                        float gx, gz;
                        readGyroXZ(gx, gz);
                        
                        float nx = gx - gyroOffsetX;
                        float nz = gz - gyroOffsetZ;

                        if (fabs(nx) < MPU_Config::GYRO_DEADZONE) nx = 0;
                        if (fabs(nz) < MPU_Config::GYRO_DEADZONE) nz = 0;

                        float speedX = (nx != 0) ? (nx > 0 ? 1 : -1) * (nx * nx) * MPU_Config::FACTOR_Y : 0;
                        float speedZ = (nz != 0) ? (nz > 0 ? 1 : -1) * (nz * nz) * MPU_Config::FACTOR_X : 0;

                        int mx = constrain((int)(-speedZ), -MPU_Config::MOUSE_MAX_SPEED, MPU_Config::MOUSE_MAX_SPEED);
                        int my = constrain((int)(-speedX), -MPU_Config::MOUSE_MAX_SPEED, MPU_Config::MOUSE_MAX_SPEED);

                        if (mx != 0 || my != 0) {
                            ble.move((int8_t)mx, (int8_t)my);
                        }
                        lastMx = mx; lastMy = my;
                    }
                    break;
            }
        }

        // Logging (2Hz)
        if (millis() - lastLog >= 500) {
            Serial.printf("[%lu] Mode:%s | T:0x%02X | XY:%d,%d | BLE:%d\n",
                          millis(), modeNames[currentMode], touchStatus, lastMx, lastMy, connected);
            lastLog = millis();
        }
    }
}