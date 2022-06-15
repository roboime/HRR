/*
 * Start.cpp
 *
 *  Created on: May 16, 2022
 *      Author: Gabriel
 */

#include "Start.hpp"
#include "Robot.hpp"

#include <cstring>

extern TIM_HandleTypeDef htim6;
extern UART_HandleTypeDef huart4;

Robot robot;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim==&htim6){
		uint8_t receivedByte = 3;
		if(HAL_UART_Receive(&huart4, &receivedByte, 1, 0) == HAL_OK){
			robot.setMovement((Robot::stepTypeDef)(receivedByte - 48));
		}
		if (robot.status == Robot::STATUS_READY){
			robot.controlCallback();	//Controle
		}
	}
}

void Start(){
	robot.init();
	while (true){

	}
}
