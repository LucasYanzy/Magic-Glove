#include "USBHIDManager.h"
#include "USB.h"
#include "USBHIDMouse.h"
#include "USBHIDKeyboard.h"

USBHIDManager::USBHIDManager() {
    _mouse = (void*)new USBHIDMouse();
    _keyboard = (void*)new USBHIDKeyboard();
}

void USBHIDManager::begin() {
    ((USBHIDMouse*)_mouse)->begin();
    ((USBHIDKeyboard*)_keyboard)->begin();
    USB.begin();
}

void USBHIDManager::pressKey(uint8_t k) {
    ((USBHIDKeyboard*)_keyboard)->press(k);
}

void USBHIDManager::releaseAll() {
    ((USBHIDKeyboard*)_keyboard)->releaseAll();
}

void USBHIDManager::leftClick() {
    ((USBHIDMouse*)_mouse)->press(0x01); 
}

void USBHIDManager::rightClick() {
    ((USBHIDMouse*)_mouse)->press(0x02); 
}

void USBHIDManager::move(int8_t x, int8_t y) {
    ((USBHIDMouse*)_mouse)->move(x, y);
}