/*
 * Robot.cpp
 *
 *  Created on: May 16, 2022
 *      Author: Gabriel
 */

#include "Robot.hpp"
#include "Defines.hpp"

#define RL 2200		//R3 da placa
#define RH 10000	//R2 da placa
#define VOLTAGE_CONVERSION (RL+RH)*3.3/(RL*4096)	//VDD = 3.3v em ADC 12 bits
#define VOLTAGE_LOW 10.0	//Limite inferior da voltagem da bateria

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart6;
extern ADC_HandleTypeDef hadc1;

Robot::Robot() {

	legs[0] = new Dynamixel(&huart1, 0, 0, 0, 4095);	//5 da mecatronica
	legs[1] = new Dynamixel(&huart2, 0, 0, 0, 4095);	//3 da mecatronica
	legs[2] = new Dynamixel(&huart3, 0, 0, 0, 4095);	//4 da mecatronica
	legs[3] = new Dynamixel(&huart6, 0, 0, 0, 4095);	//2 da mecatronica
	legs[4] = new Dynamixel(&huart1, 1, 0, 0, 4095);	//6 da mecatronica
	legs[5] = new Dynamixel(&huart2, 1, 0, 0, 4095);	//8 da mecatronica
	legs[6] = new Dynamixel(&huart3, 1, 0, 0, 4095);	//7 da mecatronica
	legs[7] = new Dynamixel(&huart6, 1, 0, 0, 4095);	//1 da mecatronica
	legs[8] = new Dynamixel(&huart1, 2, 0, 0, 4095);	//10 da mecatronica
	legs[9] = new Dynamixel(&huart2, 2, 0, 0, 4095);	//11 da mecatronica
	legs[10] = new Dynamixel(&huart3, 2, 0, 0, 4095);	//0 da mecatronica
	legs[11] = new Dynamixel(&huart6, 2, 0, 0, 4095);	//10 da mecatronica
}

void Robot::init(){
#ifdef SETID
	uint8_t id = 0;
	for(uint32_t i=0; i<2000; i++){
		leds(id);
		if(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)){
			id = (id+1) % 3;	//São 3 ID possiveis
			i=0;
			HAL_Delay(2);
			while(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin));
		}
		HAL_Delay(1);
	}
	for (int i=0; i<4; i++){
		legs[i]->setId(id);
		//legs[i]->setConfig();
	}
	error((errorTypeDef)15);	//Pisca os leds para avisar que gravou
#else
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
#endif
}

void Robot::controlCallback(){
	uint16_t data[numLegMotors][2];
	if(f_eof(&stepFile[currentStep])){
		//EOF
		f_rewind(&stepFile[currentStep]);
		//Só troca de tipo de passo depois de o atual acabar
		currentStep = nextStep();
	}
	if(batteryVoltage() < VOLTAGE_LOW){
		//Rotina para desligar os motores (pode ser no erro também)
		error(ERR_LOW_BATTERY);
	}
	for(uint32_t i=0; i<numLegMotors; i++){
		if(f_read(&stepFile[currentStep], data[i], 4, nullptr) != FR_OK){
			//SD removido
			error(ERR_NO_SD);
		}
		legs[i]->moveRelative(data[i][0], data[i][1]);
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
