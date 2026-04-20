/**
 * @file ActionMapper.h
 * @brief Maps touch sensor states to HID actions across different modes | 手势映射控制器头文件
 * @author LucasYanzy
 */

#ifndef ACTION_MAPPER_H
#define ACTION_MAPPER_H
#include <Arduino.h>
#include "BLEManager.h"

class ActionMapper {
public:
    ActionMapper(BLEManager* ble);
    
    /**
     * @brief Process current touch state and map to actions
     * @param touchState Bitmask of touched fingers (Bit0=Index, Bit1=Middle, Bit2=Ring, Bit3=Pinky)
     * @param mode Operating mode (0=WASD+Space, 1=KL, 2=Gyro)
     */
    void processAction(uint8_t touchState, uint8_t mode);

private:
    void execute(char k);
    void clickMouse(int button);

    BLEManager* _ble;
    uint8_t _lastTouchState;
};
#endif