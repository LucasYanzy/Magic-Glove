/**
 * @file BLEManager.h
 * @brief Bluetooth Low Energy HID (Keyboard/Mouse) Manager | 蓝牙 HID 管理器头文件
 * @author LucasYanzy
 */

#ifndef BLE_MANAGER_H
#define BLE_MANAGER_H
#include <Arduino.h>

class BLEManager {
public:
    BLEManager();
    void begin();
    bool isConnected();
    void pressKey(uint8_t k);
    void releaseAll();
    void leftClick();
    void rightClick();
    void move(int8_t x, int8_t y);
};
#endif