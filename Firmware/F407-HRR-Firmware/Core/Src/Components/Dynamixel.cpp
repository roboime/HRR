/*
 * Dynamixel.cpp
 *
 *  Created on: May 16, 2022
 *      Author: Gabriel
 */

#include "Dynamixel.hpp"

Dynamixel::Dynamixel(
		UART_HandleTypeDef* huartptr,
		uint8_t motorId,
		uint16_t zero,
		uint16_t lowLimit,
		uint16_t highLimit) :
		huartptr(huartptr),
		motorId(motorId),
		zero(zero),
		lowLimit(lowLimit),
		highLimit(highLimit)
{

}

void Dynamixel::init(){

}

void Dynamixel::setConfig(){

}

void Dynamixel::moveRelative(int16_t pos, uint16_t spd){
	int16_t absPos;
	absPos = (pos + zero);
	if (absPos >= lowLimit && absPos <= highLimit && spd <= 1023){
		//In range
		moveAbsolute((uint16_t)absPos, spd);
	}else{
		//Out of range, não executa
		//Deveria dar erro (será)?
	}
}

/*void Dynamixel::moveDegRadPerSecond(float pos, float spd){
	uint16_t intPos;
	uint16_t intSpd;
	intPos = 512+(pos-zeroPos)*0.1;		//Calcular sinais e valor das constantes
	intSpd = spd*10;
	if(intPos >=0 && intPos <1024){
		moveAbsolute(intPos, intSpd);
	}
}*/

void Dynamixel::moveAbsolute(uint16_t pos, uint16_t spd){
	uint8_t rxBuf[7] = {0};  // buffer vazio pra receber o status packet
	uint8_t paramArray2[2];  // buffer q vai conter a instruçao de read position
	uint8_t paramArray3[2];  // buffer q vai conter a instruçao de read speed
	paramArray2[0] = 36; // Present position (valores tabelados)
	paramArray2[1] = 2;
	paramArray3[0] = 38; // Present speed (valores tabelados)
	paramArray3[1] = 2;
	uint8_t paramArray[5];
	paramArray[0] = 30;		//Goal position
	paramArray[1] = pos;	//Conferir endianess
	paramArray[2] = pos>>8;
	paramArray[3] = spd;
	paramArray[4] = spd>>8;
	sendInstruction(0x03, paramArray, 5);  // envia a instruçao de WRITE goal position
	/*sendInstruction(0x02, paramArray2, 2);  // envia a instruçao de READ present position
	while(huartptr->gState != HAL_UART_STATE_READY); // tentativa de corrigir o bug, checa se a porta serial ta ocupada.
	HAL_HalfDuplex_EnableReceiver(huartptr);  // ativa modo receptor
	HAL_UART_Receive(huartptr, (uint8_t*) rxBuf, sizeof(rxBuf), 200);  // recebe o feedback no rxBuf
	HAL_HalfDuplex_EnableTransmitter(huartptr);  // ativa o modo transmissor
	sendInstruction(0x02, paramArray3, 2);  // envia a instruçao de read present speed
	while(huartptr->gState != HAL_UART_STATE_READY); // tentativa de corrigir o bug
	HAL_HalfDuplex_EnableReceiver(huartptr);  // ativa modo receptor
	HAL_UART_Receive(huartptr, (uint8_t*) rxBuf, sizeof(rxBuf), 200);  // recebe o feedback no rxBuf
	HAL_HalfDuplex_EnableTransmitter(huartptr);  // ativa o modo transmissor dnv
*/
}

void Dynamixel::setId(uint8_t id){
	//Vai mandar para o ID de broadcast, ppor isso não dá para usar a sendInstruction
	while(huartptr->gState != HAL_UART_STATE_READY);	//Tem que implementar timeout
	uartBuf[0] = 0xFF;				//Header
	uartBuf[1] = 0xFF;				//Header
	uartBuf[2] = 0xFE;			//ID
	uartBuf[3] = 4;		//Length
	uartBuf[4] = 0x03;		//Instruction
	uartBuf[5] = 0x03;		//ID address (modif)
	uartBuf[6] = id;
	uartBuf[7] = ~(0xFE + 4 + 0x03 + 0x03 + id);	//Checksum (modif)
	HAL_UART_Transmit_DMA(huartptr, uartBuf, 8);
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
	for(i=0; i<numParams; i++){
		uartBuf[i+5] = paramArray[i];	//Parameters
		somaParams += paramArray[i];
	}
	uartBuf[i+5] = ~(motorId + numParams + 2 + instruction + somaParams);	//Checksum
	HAL_UART_Transmit_DMA(huartptr, uartBuf, numParams+6);
}
