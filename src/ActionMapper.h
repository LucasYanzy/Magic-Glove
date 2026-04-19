#ifndef ACTION_MAPPER_H
#define ACTION_MAPPER_H
#include <Arduino.h>
#include "BLEManager.h"

class ActionMapper {
public:
    ActionMapper(BLEManager* ble);
    // mode: 0=WASD+Space, 1=KL, 2=Gyro(clicks only)
    void processAction(uint8_t touchState, uint8_t mode);

private:
    void execute(char k);
    void clickMouse(int button);

    BLEManager* _ble;
    uint8_t _lastTouchState;
};
#endif