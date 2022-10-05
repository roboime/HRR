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
	Dynamixel(UART_HandleTypeDef* huartptr, uint8_t motorId, uint16_t zeroPos, uint16_t lowLimitPos, uint16_t highLimitPos);
	void init();
	void setConfig();
	void moveRelative(int16_t pos, uint16_t spd);
	void moveDegRadPerSecond(float pos, float spd);
	void moveAbsolute(uint16_t pos, uint16_t spd);
private:
	UART_HandleTypeDef* huartptr;
	uint8_t motorId;
	uint8_t uartBuf[64];
	uint16_t zero;
	uint16_t lowLimit;
	uint16_t highLimit;
	void sendInstruction(uint8_t instruction, uint8_t* paramArray, uint8_t numParams);
	void sendInstruction2(uint8_t instruction, uint8_t* paramArray, uint8_t numParams);

//Função nova adicionada:

	void receivePackage(uint8_t instruction, uint8_t* paramArray, uint8_t numParams);
};

#endif /* SRC_COMPONENTS_DYNAMIXEL_HPP_ */
