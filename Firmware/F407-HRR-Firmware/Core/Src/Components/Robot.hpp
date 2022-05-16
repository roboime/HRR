/*
 * Robot.hpp
 *
 *  Created on: May 16, 2022
 *      Author: Gabriel
 */

#ifndef SRC_COMPONENTS_ROBOT_HPP_
#define SRC_COMPONENTS_ROBOT_HPP_

#include "main.h"
#include "Dynamixel.hpp"
#include "PWMServo.hpp"

class Robot {
public:
	Robot();
private:
	Dynamixel* legs;
	PWMServo* arms;
};

#endif /* SRC_COMPONENTS_ROBOT_HPP_ */
