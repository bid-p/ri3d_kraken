#include "subsystems/chassis.hpp"
#include "main.h"

namespace chassis {

chassisStates currState = notRunning;

Motor chasR1(CHAS_R1, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees, Logger::getDefaultLogger());
Motor chasR2(CHAS_R2, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees, Logger::getDefaultLogger());
Motor chasL1(CHAS_L1, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees, Logger::getDefaultLogger());
Motor chasL2(CHAS_L2, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees, Logger::getDefaultLogger());

okapi::MotorGroup rightMotorGroup({-CHAS_R1, -CHAS_R2});
okapi::MotorGroup leftMotorGroup({CHAS_L1, CHAS_L2});

std::shared_ptr<ChassisController> chassisController = ChassisControllerBuilder()
                                                           .withMotors(leftMotorGroup, rightMotorGroup)
                                                           .withDimensions(AbstractMotor::gearset::green, {{4_in, 11.5_in}, imev5GreenTPR})
                                                           .build();

void task(void* param) {

    while (true) {
        update();

        act();

        pros::delay(10);
    }
}

void update() {
    currState = notRunning;
    if (abs(controller.getAnalog(ControllerAnalog::leftY)) > JOY_DEADBAND ||
        abs(controller.getAnalog(ControllerAnalog::rightX)) > JOY_DEADBAND) {
        currState = running;
    }
}

void act() {

    switch (currState) {
    case notRunning:
        chassisController->getModel()->setMaxVelocity(200);
        chassisController->getModel()->setBrakeMode(AbstractMotor::brakeMode::coast);
        chassisController->getModel()->stop();
        break;

    case running:
        chassisController->getModel()->arcade(controller.getAnalog(ControllerAnalog::leftY),
                                              controller.getAnalog(ControllerAnalog::rightX));
        break;
    }
}

} // namespace chassis