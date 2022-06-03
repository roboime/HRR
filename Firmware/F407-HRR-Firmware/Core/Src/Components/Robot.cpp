/*
 * Robot.cpp
 *
 *  Created on: May 16, 2022
 *      Author: Gabriel
 */

#include "Robot.hpp"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart6;

Robot::Robot() {
	legs[0] = new Dynamixel(&huart1, 0);
	legs[1] = new Dynamixel(&huart2, 0);
	legs[2] = new Dynamixel(&huart3, 0);
	legs[3] = new Dynamixel(&huart6, 0);
	legs[4] = new Dynamixel(&huart1, 1);
	legs[5] = new Dynamixel(&huart2, 1);
	legs[6] = new Dynamixel(&huart3, 1);
	legs[7] = new Dynamixel(&huart6, 1);
	legs[8] = new Dynamixel(&huart1, 2);
	legs[9] = new Dynamixel(&huart2, 2);
	legs[10] = new Dynamixel(&huart3, 2);
	legs[11] = new Dynamixel(&huart6, 2);
}

void Robot::init(){
	FRESULT res[numStepTypes];
	//TODO: Conferir os passos de transição 4 e 5
	for (uint32_t i=0; i<numStepTypes; i++){
		res[i] = f_open(&stepFile[i], stepFilePaths[i].c_str(), FA_OPEN_EXISTING | FA_READ);
		if(res[i]){
			if(res[i] == FR_NOT_READY){
				//Sem SD
				error(ERR_NO_SD);
			}else if(res[i] == FR_NO_FILE || res[i] == FR_NO_PATH){
				//Arquivo não encontrado
				error(ERR_FILE_NOT_FOUND);
			}
		}
	}
	leds(status = STATUS_READY);
}

void Robot::controlCallback(){
	uint16_t data[numLegMotors][2];
	for(uint32_t i=0; i<numLegMotors; i++){
		//legs[i]->move(0, 0);
		f_read(&stepFile[0], data[i], 4, NULL);
	}
}

void Robot::setMovement(stepTypeDef step){

}

void Robot::error(errorTypeDef error){
	status = STATUS_ERROR;
	while (true){
		leds(error);
		HAL_Delay(100);
		leds(0);
		HAL_Delay(100);
	}
}

void Robot::leds(uint8_t binary){
	HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, (GPIO_PinState)(binary & 1));
	HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, (GPIO_PinState)((binary>>1) & 1));
	HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, (GPIO_PinState)((binary>>2) & 1));
	HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, (GPIO_PinState)((binary>>3) & 1));
}
