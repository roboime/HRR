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
	enum stepTypeDef{
		STEP_FORWARD = 0,
		STEP_LEFT,
		STEP_RIGHT,
		STEP_STOP
	};
	bool ready = false;
	Robot();
	void init();
	void controlCallback();
	void setMovement(stepTypeDef step);
private:
	static const uint32_t numLegMotors = 12;
	static const uint32_t numArmMotors = 6;
	static const uint32_t controlFreq = 400;
	Dynamixel* legs[numLegMotors];
	PWMServo* arms[numArmMotors];
	float legsZeroArray[numLegMotors];
	float armsZeroArray[numArmMotors];
};

#endif /* SRC_COMPONENTS_ROBOT_HPP_ */
