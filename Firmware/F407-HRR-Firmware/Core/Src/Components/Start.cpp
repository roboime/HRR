/*
 * Start.cpp
 *
 *  Created on: May 16, 2022
 *      Author: Gabriel
 */

#include "Start.hpp"
#include "Robot.hpp"

#include <cstring>
#include "fatfs.h"

extern TIM_HandleTypeDef htim6;

Robot robot;

FIL outLog;
const char* helloworld = "Hello World!!!";

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim==&htim6){
		if (robot.ready){
			robot.controlCallback();	//Controle
		}
	}
}

void Start(){
	robot.init();
	FRESULT res;
	if(res = f_open(&outLog, "0:outLog.txt", FA_CREATE_ALWAYS | FA_WRITE)){
		//Error
	}else{
		//OK
		f_write(&outLog, helloworld, strlen(helloworld), NULL);
	}
	f_close(&outLog);
	while (true){
		robot.setMovement(Robot::STEP_FORWARD);
	}
}
