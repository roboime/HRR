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
	void setStepType(uint8_t stepType);
private:
	Dynamixel* legs[12];
	PWMServo* arms[6];
};

#endif /* SRC_COMPONENTS_ROBOT_HPP_ */
