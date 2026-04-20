/**
 * @file BLEManager.cpp
 * @brief Bluetooth Low Energy HID (Keyboard/Mouse) Manager | 蓝牙 HID 管理器实现
 * @author LucasYanzy
 */

#include "BLEManager.h"
#include <BleComboKeyboard.h>
#include <BleComboMouse.h>

// Custom BLE device name: "Magic Glove" (Updated from Magic MouseX) | 蓝牙设备名称
static BleComboKeyboard bleKeyboard("Magic Glove", "GestureGlove", 100);
static BleComboMouse    bleMouse(&bleKeyboard);

BLEManager::BLEManager() {}

void BLEManager::begin() {
    bleKeyboard.begin();
    bleMouse.begin();
}

bool BLEManager::isConnected() {
    return bleKeyboard.isConnected();
}

void BLEManager::pressKey(uint8_t k) {
    if (isConnected()) bleKeyboard.press(k);
}

void BLEManager::releaseAll() {
    if (isConnected()) {
        bleKeyboard.releaseAll();
        bleMouse.release(MOUSE_LEFT);
        bleMouse.release(MOUSE_RIGHT);
    }
}

void BLEManager::leftClick() {
    if (isConnected()) bleMouse.press(MOUSE_LEFT);
}

void BLEManager::rightClick() {
    if (isConnected()) bleMouse.press(MOUSE_RIGHT);
}

void BLEManager::move(int8_t x, int8_t y) {
    if (isConnected()) bleMouse.move(x, y);
}