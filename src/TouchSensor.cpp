#include "TouchSensor.h"

const int DEFAULT_TOUCH_PINS[TOUCH_COUNT] = {1, 2, 3, 4}; 

TouchSensor::TouchSensor(const int* pins) {
    for (int i = 0; i < TOUCH_COUNT; i++) _pins[i] = pins[i];
}

void TouchSensor::begin() {
    for (int i = 0; i < TOUCH_COUNT; i++) {
        _debounceCounter[i] = 0;
        _currentState[i] = false;
    }
    calibrate();
}

void TouchSensor::calibrate() {
    pinMode(LED_BUILTIN, OUTPUT);
    for (int i = 0; i < 6; i++) {  // Reduced from 10 to 6 to save time
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        delay(100);  // Reduced from 150ms
        yield();     // Feed watchdog
    }
    readBaseline();
    digitalWrite(LED_BUILTIN, LOW); 
}

void TouchSensor::readBaseline() {
    uint32_t sum[TOUCH_COUNT] = {0};
    for (int sample = 0; sample < 10; sample++) {
        for (int i = 0; i < TOUCH_COUNT; i++) sum[i] += touchRead(_pins[i]);
        delay(10);
        yield(); // Feed watchdog
    }
    for (int i = 0; i < TOUCH_COUNT; i++) _baseline[i] = sum[i] / 10;
}

void TouchSensor::update() {
    for (int i = 0; i < TOUCH_COUNT; i++) {
        uint16_t value = touchRead(_pins[i]);
        // Corrected logical operator for ESP32-S3
        bool touched = (value > (_baseline[i] + TOUCH_THRESHOLD)); 
        
        if (touched != _currentState[i]) {
            if (++_debounceCounter[i] >= DEBOUNCE_COUNT) {
                _currentState[i] = touched;
                _debounceCounter[i] = 0;
            }
        } else {
            _debounceCounter[i] = 0;
        }
    }
}

uint8_t TouchSensor::getTouchState() {
    uint8_t state = 0;
    for (int i = 0; i < TOUCH_COUNT; i++) if (_currentState[i]) state |= (1 << i);
    return state;
}