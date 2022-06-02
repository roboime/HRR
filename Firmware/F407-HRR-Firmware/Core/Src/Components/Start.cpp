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

Robot robot;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim==&htim6){
		if (robot.status == Robot::STATUS_READY){
			robot.controlCallback();	//Controle
		}
	}
}

void Start(){
	robot.init();
	while (true){
		robot.setMovement(Robot::STEP_FORWARD);
	}
}
