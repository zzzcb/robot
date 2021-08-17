// File:          my_controller.cpp
// Date:
// Description:
// Author:
// Modifications:

// You may need to add webots include files such as
// <webots/DistanceSensor.hpp>, <webots/Motor.hpp>, etc.
// and/or to add some other includes
#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>

// All the webots classes are defined in the "webots" namespace
using namespace webots;
using namespace std;

// This is the main program of your controller.
// It creates an instance of your Robot instance, launches its
// function(s) and destroys it at the end of the execution.
// Note that only one instance of Robot should be created in
// a controller program.
// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node
int main(int argc, char **argv) {
    // create the Robot instance.
    Robot *robot = new Robot();

    // get the time step of the current world.
    int timeStep = (int) robot->getBasicTimeStep();

    // You should insert a getDevice-like function in order to get the
    // instance of a device of the robot. Something like:
    //  Motor *motor = robot->getMotor("motorname");
    //  DistanceSensor *ds = robot->getDistanceSensor("dsname");
    //  ds->enable(timeStep);

    Motor *wheels[4];
    string wheels_names[4] = {"front_left_wheel_motor", "front_right_wheel_motor", "behind_left_wheel_motor",
                                   "behind_right_wheel_motor",};
    for (int i = 0; i < 4; i++) {
        wheels[i] = robot->getMotor(wheels_names[i]);
        wheels[i]->setPosition(INFINITY);
        wheels[i]->setVelocity(0.0);
    }

    DistanceSensor *ds[2];
    string dsNames[2] = {"ds_right", "ds_left"};
    for (int i = 0; i < 2; i++) {
        ds[i] = robot->getDistanceSensor(dsNames[i]);
        ds[i]->enable(timeStep);
    }

    double CAR_SPEED = 2.0;
    double leftSpeed,rightSpeed;
    int cnt = 0;

    // Main loop:
    // - perform simulation steps until Webots is stopping the controller
    while (robot->step(timeStep) != -1) {
        // Read the sensors:
        // Enter here functions to read sensor data, like:
        //  double val = ds->getValue();
        bool turnRight = false;  // 遇到障碍物 只向右转

        if(cnt > 0){ // 多转几次
            cnt--;
            continue;
        }

        for (int i = 0; i < 2; ++i) {
            if (ds[i]->getValue() < 500) {
                turnRight = true;
                cnt = 100;
                break;
            }
        }
        if (turnRight) {
            leftSpeed = CAR_SPEED;
            rightSpeed = -CAR_SPEED;
        } else {
            leftSpeed = CAR_SPEED;
            rightSpeed = CAR_SPEED;
        }


        wheels[0]->setVelocity(leftSpeed);
        wheels[1]->setVelocity(rightSpeed);
        wheels[2]->setVelocity(leftSpeed);
        wheels[3]->setVelocity(rightSpeed);

        // Process sensor data here.

        // Enter here functions to send actuator commands, like:
        //  motor->setPosition(10.0);
    };

    // Enter here exit cleanup code.

    delete robot;
    return 0;
}
