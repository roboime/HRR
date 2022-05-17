/*
 * Start.cpp
 *
 *  Created on: May 16, 2022
 *      Author: Gabriel
 */

#include "Start.hpp"
#include "Robot.hpp"

extern TIM_HandleTypeDef htim6;

Robot robot;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim==&htim6){
		if (robot.ready){
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
