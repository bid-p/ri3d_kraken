#pragma once

#include "main.h"

namespace chassis {

enum chassisStates {
    notRunning = 'x',
    running = 'r'
};
extern chassisStates currState;

extern Motor chasR1, chasR2, chasL1, chasL2;

extern std::shared_ptr<ChassisController> chassisController;

extern void update();
extern void act();
extern void task(void* param);

} // namespace chassis
