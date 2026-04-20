/**
 * @file Buzzer.cpp
 * @brief Simple passive buzzer manager for status feedback | 无源蜂鸣器状态反馈管理器实现
 * @author LucasYanzy
 */

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

/**
 * @brief Boot success sound: Two quick beeps | 开机成功音效：急促两声
 */
void Buzzer::bootSuccess() {
    beep(50, 2);
}

/**
 * @brief Mode change sound: Beeps equal to (mode+1) | 模式切换音效：(模式编号+1)声
 */
void Buzzer::modeChanged(uint8_t mode) {
    beep(100, mode + 1);
}

/**
 * @brief Connection change sound: Ascending for connect, descending for disconnect 
 * | 连接状态变化音效：连接为升调，断开为降调
 */
void Buzzer::connectionChanged(bool connected) {
    if (connected) {
        // Ascending beep | 升调起音
        digitalWrite(_pin, HIGH); delay(50);
        digitalWrite(_pin, LOW);  delay(30);
        digitalWrite(_pin, HIGH); delay(100);
        digitalWrite(_pin, LOW);
    } else {
        // Descending beep | 降调退音
        digitalWrite(_pin, HIGH); delay(100);
        digitalWrite(_pin, LOW);  delay(30);
        digitalWrite(_pin, HIGH); delay(50);
        digitalWrite(_pin, LOW);
    }
}
