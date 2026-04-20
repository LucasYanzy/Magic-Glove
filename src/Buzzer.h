/**
 * @file Buzzer.h
 * @brief Simple passive buzzer manager for status feedback | 无源蜂鸣器状态反馈管理器头文件
 * @author LucasYanzy
 */

#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

class Buzzer {
public:
    Buzzer(int pin);
    void begin();
    
    // Simple beep | 简单蜂鸣
    void beep(int durationMs = 100, int count = 1);
    
    // Special patterns | 特殊提示音效
    void bootSuccess();
    void modeChanged(uint8_t mode);
    void connectionChanged(bool connected);

private:
    int _pin;
};

#endif
