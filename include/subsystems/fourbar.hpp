#pragma once

#include "main.h"

namespace fourbar {

enum fourbarStates {
    notRunning = 'x',
    up = 'u',
    down = 'd',
    hold = 'h',
    yield = 'y'
};
extern fourbarStates currState;

extern Motor fourbar1;

extern void update();
extern void act();
extern void task(void* param);

} // namespace fourbar
