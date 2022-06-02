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
#include "fatfs.h"
#include <string>


class Robot {
public:
	enum stepTypeDef{
		STEP_FORWARD = 0,
		STEP_LEFT,
		STEP_RIGHT,
		STEP_STOP
	};
	enum errorTypeDef{
		ERR_OK = 0,
		ERR_NO_SD,
		ERR_FILE_NOT_FOUND
	};
	enum statusTypeDef{
		STATUS_NOT_INITIALIZED = 0,
		STATUS_READY,
		STATUS_ERROR
	};
	statusTypeDef status = STATUS_NOT_INITIALIZED;
	Robot();
	void init();
	void controlCallback();
	void setMovement(stepTypeDef step);
	void error(errorTypeDef error);
	void leds(uint8_t binary);
private:
	static const uint32_t numLegMotors = 12;
	static const uint32_t numArmMotors = 6;
	static const uint32_t controlFreq = 400;
	static const uint32_t numStepTypes = 6;
	const std::string stepFilePaths[numStepTypes] = {
			"0:Steps/frente.csv",
			"0:Steps/esquerda.csv",
			"0:Steps/direita.csv",
			"0:Steps/parado.csv",
			"0:Steps/0-3.csv",
			"0:Steps/3-0.csv"
	};
	FIL stepFile[numStepTypes];
	Dynamixel* legs[numLegMotors];
	PWMServo* arms[numArmMotors];
	float legsZeroArray[numLegMotors];
	float armsZeroArray[numArmMotors];
};

#endif /* SRC_COMPONENTS_ROBOT_HPP_ */
