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
		uint8_t receivedByte;
		if(HAL_UART_Receive(&huart4, &receivedByte, 1, 0) == HAL_OK){	//Verifica se recebeu byte na porta serial
			robot.setMovement((Robot::stepTypeDef)(receivedByte - 48));	//Combinado com a intel de receber em ASCII
		}
		if (robot.status == Robot::STATUS_READY){
			robot.controlCallback();	//Controle
		}
	}
}

void Start(){
	robot.init();
	robot.setMovement(Robot::STEP_FORWARD);  //Força o robô a andar
	while (true){
		//Não faz nada (tudo na interrupção e na máquina de estados)
	}
}
