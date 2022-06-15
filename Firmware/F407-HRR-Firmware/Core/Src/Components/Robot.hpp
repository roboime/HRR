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
		STEP_STOP,
		STEP_FIRST,
		STEP_LAST,
		STEP_CLIMB,
		STEP_DESCENT
	};
	enum errorTypeDef{
		ERR_OK = 0,
		ERR_NO_SD,
		ERR_FILE_NOT_FOUND,
		ERR_LOW_BATTERY,
		ERR_MISC
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
	float batteryVoltage();
private:
	static const uint32_t numLegMotors = 12;
	static const uint32_t numArmMotors = 6;
	static const uint32_t controlFreq = 100;
	static const uint32_t numStepTypes = 8;
	const std::string stepFilePaths[numStepTypes] = {
			"0:Steps/forward.bin",
			"0:Steps/left.bin",
			"0:Steps/right.bin",
			"0:Steps/stop.bin",
			"0:Steps/first.bin",
			"0:Steps/last.bin",
			"0:Steps/climb.bin",
			"0:Steps/descent.bin"
	};
	FIL stepFile[numStepTypes];
	Dynamixel* legs[numLegMotors];
	PWMServo* arms[numArmMotors];
	volatile uint32_t battInt = 4095;
	stepTypeDef currentStep = STEP_STOP;	//Começa parado
	stepTypeDef desiredStep = STEP_STOP;
	stepTypeDef nextStep();
};

#endif /* SRC_COMPONENTS_ROBOT_HPP_ */
