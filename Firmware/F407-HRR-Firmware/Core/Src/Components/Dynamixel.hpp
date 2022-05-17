/*
 * Dynamixel.hpp
 *
 *  Created on: May 16, 2022
 *      Author: Gabriel
 */

#ifndef SRC_COMPONENTS_DYNAMIXEL_HPP_
#define SRC_COMPONENTS_DYNAMIXEL_HPP_

#include "main.h"

class Dynamixel {
public:
	Dynamixel(UART_HandleTypeDef* huartptr, uint8_t motorId);
	void init();
	void setZero(float pos);
	void move(float pos, float spd);
private:
	UART_HandleTypeDef* huartptr;
	uint8_t motorId;
	uint8_t uartBuf[64];
	float zeroPos = 0;
	void moveInt(uint16_t pos, uint16_t spd);
	void sendInstruction(uint8_t instruction, uint8_t* paramArray, uint8_t numParams);
};

#endif /* SRC_COMPONENTS_DYNAMIXEL_HPP_ */
