#include "subsystems/spinner.hpp"
#include "main.h"

ControllerButton spinnerFwdBtn = controller[ControllerDigital::left];
ControllerButton spinnerBckBtn = controller[ControllerDigital::right];

namespace spinner {

spinnerStates currState = notRunning;

Motor spinner1(SPINNER_1, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees, Logger::getDefaultLogger());

void task(void* param) {

    while (true) {
        update();

        act();

        pros::delay(10);
    }
}

void update() {
    currState = notRunning;
    pros::lcd::print(4, "spinner state: %c | spinner Enc: %d", currState, (int)spinner1.getPosition());
    // printf("spinner state: %c | spinner Enc: %d\n", currState, (int)spinner1.getPosition());
    if (spinnerFwdBtn.isPressed()) {
        currState = forward;
    }
    if (spinnerBckBtn.isPressed()) {
        currState = reverse;
    }
}

void act() {
    switch (currState) {
    case notRunning:
        spinner1.setBrakeMode(AbstractMotor::brakeMode::brake);
        spinner1.moveVelocity(0);
        break;

    case forward:
        spinner1.moveVelocity(100);
        break;

    case reverse:
        spinner1.moveVelocity(-100);
        break;
    }
}

} // namespace spinner