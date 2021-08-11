#include "subsystems/fourbar.hpp"
#include "main.h"

ControllerButton liftUpBtn = controller[ControllerDigital::R1];
ControllerButton liftDownBtn = controller[ControllerDigital::R2];

namespace fourbar {

fourbarStates currState = notRunning;

Motor fourbar1(FOURBAR_1, true, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees, Logger::getDefaultLogger());

void task(void* param) {

    while (true) {
        update();

        act();

        pros::delay(10);
    }
}

void update() {
    currState = hold;
    pros::lcd::print(3, "fourbar state: %c | fourbar Enc: %d", currState, (int)fourbar1.getPosition());
    // printf("fourbar state: %c | fourbar Enc: %d\n", currState, (int)fourbar1.getPosition());
    if (liftUpBtn.isPressed()){
        currState = up;
    }
    if (liftDownBtn.isPressed()){
        currState = down;
    }
}

void act() {

    switch (currState) {
    case notRunning:
        fourbar1.setBrakeMode(AbstractMotor::brakeMode::coast);
        fourbar1.moveVelocity(0);
        break;

    case up:
        fourbar1.moveVelocity(100);
        break;

    case down:
        fourbar1.moveVelocity(-100);
        break;

    case hold:
        fourbar1.setBrakeMode(AbstractMotor::brakeMode::hold);
        fourbar1.moveVelocity(0);
        break;
    }
}

} // namespace fourbar