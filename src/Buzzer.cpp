#include "Buzzer.h"

Buzzer::Buzzer(int pin) : _pin(pin) {}

void Buzzer::begin() {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
}

void Buzzer::beep(int durationMs, int count) {
    for (int i = 0; i < count; i++) {
        digitalWrite(_pin, HIGH);
        delay(durationMs);
        digitalWrite(_pin, LOW);
        if (i < count - 1) delay(durationMs);
    }
}

void Buzzer::bootSuccess() {
    // Two quick high beeps
    beep(50, 2);
}

void Buzzer::modeChanged(uint8_t mode) {
    // Beep 'mode + 1' times
    beep(100, mode + 1);
}

void Buzzer::connectionChanged(bool connected) {
    if (connected) {
        // Ascending beep
        digitalWrite(_pin, HIGH); delay(50);
        digitalWrite(_pin, LOW);  delay(30);
        digitalWrite(_pin, HIGH); delay(100);
        digitalWrite(_pin, LOW);
    } else {
        // Descending beep
        digitalWrite(_pin, HIGH); delay(100);
        digitalWrite(_pin, LOW);  delay(30);
        digitalWrite(_pin, HIGH); delay(50);
        digitalWrite(_pin, LOW);
    }
}
