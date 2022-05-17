/*
 * Dynamixel.cpp
 *
 *  Created on: May 16, 2022
 *      Author: Gabriel
 */

#include "Dynamixel.hpp"

Dynamixel::Dynamixel(
		UART_HandleTypeDef* huartptr,
		uint8_t motorId) :
		huartptr(huartptr),
		motorId(motorId)
{

}

void Dynamixel::init(){

}

void Dynamixel::setZero(float pos){
	zeroPos = pos;
}

void Dynamixel::move(float pos, float spd){
	uint16_t intPos;
	uint16_t intSpd;
	intPos = 512+(pos-zeroPos)*0.1;		//Calcular sinais e valor das constantes
	intSpd = spd*10;
	if(intPos >=0 && intPos <1024){
		moveInt(intPos, intSpd);
	}
}

void Dynamixel::moveInt(uint16_t pos, uint16_t spd){
	uint8_t paramArray[4];
	paramArray[0] = pos;	//Conferir endianess
	paramArray[1] = pos>>8;
	paramArray[2] = spd;
	paramArray[3] = spd>>8;
	sendInstruction(0x03, paramArray, 4);
}

void Dynamixel::sendInstruction(uint8_t instruction, uint8_t* paramArray, uint8_t numParams){
	while(huartptr->gState != HAL_UART_STATE_READY);	//Tem que implementar timeout
	uartBuf[0] = 0xFF;				//Header
	uartBuf[1] = 0xFF;				//Header
	uartBuf[2] = motorId;			//ID
	uartBuf[3] = numParams + 2;		//Length
	uartBuf[4] = instruction;		//Instruction
	uint8_t i;
	uint8_t somaParams = 0;
	for(i=5; i<numParams+5; i++){
		uartBuf[i] = paramArray[i];	//Parameters
		somaParams += paramArray[i];
	}
	uartBuf[i] = ~(motorId + numParams + 2 + instruction + somaParams);	//Checksum
	HAL_UART_Transmit_DMA(huartptr, uartBuf, numParams+6);
}
