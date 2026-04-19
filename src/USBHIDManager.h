#ifndef USB_HID_MANAGER_H
#define USB_HID_MANAGER_H
#include <Arduino.h>

class USBHIDManager {
public:
    USBHIDManager();
    void begin();
    void pressKey(uint8_t k);
    void releaseAll();
    void leftClick();
    void rightClick();
    void move(int8_t x, int8_t y);
private:
    void* _mouse;
    void* _keyboard;
};
#endif