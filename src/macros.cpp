#include "main.h"
#include "macros.hpp"
#include "subsystems/chassis.hpp"
#include "subsystems/mogo.hpp"
#include "subsystems/fourbar.hpp"
#include "subsystems/spinner.hpp"

using namespace okapi;

ControllerButton mogoToggleBtn = controller[ControllerDigital::B];

namespace macro {

bool mogoToggleState = false; // in is false, out is true
int mogoInVal = 0;
int mogoOutVal = 1005;

macroStates currState = none;

void update() {
    printf("Macro state: %c | Mogo Enc: %d\n", currState, mogo::mogo1.getPosition());
    currState = none;
    if (mogoToggleBtn.changedToPressed()) {
        mogoToggleState = !mogoToggleState;

        currState = mogoToggle;
    }
} // namespace macro

void act() {
    switch (currState) {
    case none: // macro is not activated
        break;
    case mogoToggle:
        mogo::currState = mogo::yield;
        if (mogoToggleState) {
            mogo::mogo1.moveAbsolute(mogoInVal, 100);
        }
        else {
            mogo::mogo1.moveAbsolute(mogoOutVal, 100);
        }
        break;
    }
}

void task(void* param){

    while (true){
        update();

        act();

        pros::delay(10);
    }
}

void resetSubsystems() {
    chassis::currState = chassis::notRunning;
    mogo::currState = mogo::notRunning;
    fourbar::currState = fourbar::notRunning;
    spinner::currState = spinner::notRunning;
}

} // namespace macro