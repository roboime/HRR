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
	ready = true;
}

void Robot::controlCallback(){
	for(uint32_t i=0; i<numLegMotors; i++){
		legs[i]->move(0, 0);
	}
}

void Robot::setMovement(stepTypeDef step){

}
