#pragma once

#include "main.h"

namespace spinner {

enum spinnerStates {
    notRunning = 'x',
    forward = 'f',
    reverse = 'r',
    yield = 'y'
};
extern spinnerStates currState;

extern Motor spinner1;

extern void update();
extern void act();
extern void task(void* param);

} // namespace spinner