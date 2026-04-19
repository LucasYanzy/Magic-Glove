#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

class Buzzer {
public:
    Buzzer(int pin);
    void begin();
    
    // Simple beep
    void beep(int durationMs = 100, int count = 1);
    
    // Special patterns
    void bootSuccess();
    void modeChanged(uint8_t mode);
    void connectionChanged(bool connected);

private:
    int _pin;
};

#endif
