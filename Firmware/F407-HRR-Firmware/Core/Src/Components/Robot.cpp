/*
 * Robot.cpp
 *
 *  Created on: May 16, 2022
 *      Author: Gabriel
 */

#include "Robot.hpp"

#define RL 2200		//R3 da placa
#define RH 10000	//R2 da placa
#define VOLTAGE_CONVERSION (RL+RH)*3.3/(RL*4096)	//VDD = 3.3v em ADC 12 bits
#define VOLTAGE_LOW 10.5	//Limite inferior da voltagem da bateria

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart6;
extern ADC_HandleTypeDef hadc1;

Robot::Robot() {

	legs[0] = new Dynamixel(&huart1, 0, 512, 0, 1023);
	legs[1] = new Dynamixel(&huart2, 0, 512, 0, 1023);
	legs[2] = new Dynamixel(&huart3, 0, 512, 0, 1023);
	legs[3] = new Dynamixel(&huart6, 0, 512, 0, 1023);
	legs[4] = new Dynamixel(&huart1, 1, 512, 0, 1023);
	legs[5] = new Dynamixel(&huart2, 1, 512, 0, 1023);
	legs[6] = new Dynamixel(&huart3, 1, 512, 0, 1023);
	legs[7] = new Dynamixel(&huart6, 1, 512, 0, 1023);
	legs[8] = new Dynamixel(&huart1, 2, 512, 0, 1023);
	legs[9] = new Dynamixel(&huart2, 2, 512, 0, 1023);
	legs[10] = new Dynamixel(&huart3, 2, 512, 0, 1023);
	legs[11] = new Dynamixel(&huart6, 2, 512, 0, 1023);
}

void Robot::init(){
	FRESULT res[numStepTypes];
	for (uint32_t i=0; i<numStepTypes; i++){
		res[i] = f_open(&stepFile[i], stepFilePaths[i].c_str(), FA_OPEN_EXISTING | FA_READ);
		if(res[i]){
			if(res[i] == FR_NOT_READY){
				//Sem SD
				error(ERR_NO_SD);
			}else if(res[i] == FR_NO_FILE || res[i] == FR_NO_PATH){
				//Arquivo não encontrado
				error(ERR_FILE_NOT_FOUND);
			}else{
				error(ERR_MISC);
			}
		}
	}
	leds(status = STATUS_READY);
}

void Robot::controlCallback(){
	uint16_t data[numLegMotors][2];
	if(f_eof(&stepFile[currentStep])){
		//EOF
		f_rewind(&stepFile[currentStep]);
		//Só troca de tipo de passo depois de o atual acabar
		currentStep = nextStep();
	}
	for(uint32_t i=0; i<numLegMotors; i++){
		if(f_read(&stepFile[currentStep], data[i], 4, nullptr) != FR_OK){
			//SD removido
			error(ERR_NO_SD);
		}
		legs[i]->moveRelative(data[i][0], data[i][1]);
	}
	if(batteryVoltage() < VOLTAGE_LOW){
		//Rotina para desligar os motores (pode ser no erro também)
		error(ERR_LOW_BATTERY);
	}
}

void Robot::setMovement(stepTypeDef step){
	desiredStep = step;
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

float Robot::batteryVoltage(){
	float voltage = battInt*VOLTAGE_CONVERSION;	//12 bits
	HAL_ADC_Stop_DMA(&hadc1);
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&battInt, 1);
	return voltage;
}

Robot::stepTypeDef Robot::nextStep(){
	switch (currentStep){
	case STEP_FORWARD:
		if(desiredStep == STEP_FORWARD){
			return STEP_FORWARD;
		}else{
			return STEP_LAST;
		}
		break;
	case STEP_LEFT:
		if(desiredStep == STEP_FORWARD){
			return STEP_FIRST;
		}else{
			return desiredStep;
		}
		break;
	case STEP_RIGHT:
		if(desiredStep == STEP_FORWARD){
			return STEP_FIRST;
		}else{
			return desiredStep;
		}
		break;
	case STEP_STOP:
		if(desiredStep == STEP_FORWARD){
			return STEP_FIRST;
		}else{
			return desiredStep;
		}
		break;
	case STEP_FIRST:
		if(desiredStep == STEP_FORWARD){
			return STEP_FORWARD;
		}else{
			return STEP_LAST;
		}
		break;
	case STEP_LAST:
		if(desiredStep == STEP_FORWARD){
			return STEP_FIRST;
		}else{
			return desiredStep;
		}
		break;
	case STEP_CLIMB:
		if(desiredStep == STEP_FORWARD){
			return STEP_FIRST;
		}else{
			return desiredStep;
		}
		break;
	case STEP_DESCENT:
		if(desiredStep == STEP_FORWARD){
			return STEP_FIRST;
		}else{
			return desiredStep;
		}
		break;
	}
	return STEP_STOP;	//Para não dar warning na compilação
}
