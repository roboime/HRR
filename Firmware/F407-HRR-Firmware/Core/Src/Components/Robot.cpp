/*
 * Robot.cpp
 *
 *  Created on: May 16, 2022
 *      Author: Gabriel
 */

#include "Robot.hpp"

Robot::Robot() {
	legs = new Dynamixel[12];
	arms = new PWMServo[6];
}

