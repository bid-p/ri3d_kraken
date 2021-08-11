#include "main.h"
#include "init.hpp"

#include "subsystems/chassis.hpp"
#include "subsystems/mogo.hpp"
#include "subsystems/fourbar.hpp"
#include "subsystems/spinner.hpp"
#include "subsystems/chainbar.hpp"
#include "subsystems/intake.hpp"

#include "macros.hpp"

Controller controller = Controller();

pros::Task *chassisTask;
pros::Task *mogoTask;
pros::Task *fourbarTask;
pros::Task *chainbarTask;
pros::Task *spinnerTask;
pros::Task *intakeTask;

pros::Task *macroTask;

void initializeAllTasks() {
    chassisTask = new pros::Task(chassis::task, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Chassis Task");
    mogoTask = new pros::Task(mogo::task, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Mogo Task");
    fourbarTask = new pros::Task(fourbar::task, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Fourbar Task");
    spinnerTask = new pros::Task(spinner::task, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Spinner Task");
    chainbarTask = new pros::Task(chainbar::task, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Chainbar Task");
    intakeTask = new pros::Task(intake::task, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Intake Task");

    macroTask = new pros::Task(macro::task, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Macro Task");
}
