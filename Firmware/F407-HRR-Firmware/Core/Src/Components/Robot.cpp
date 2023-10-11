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
#define VOLTAGE_LOW 0	//Limite inferior da voltagem da bateria

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart6;
extern ADC_HandleTypeDef hadc1;

Robot::Robot() {
//								Porta	ID	Zero Min Max
        legs[5] = new Dynamixel(&huart1, 0, 357, 0, 1023);	//5 da mecatronica PB6 (ok)
		legs[3] = new Dynamixel(&huart2, 0, 357, 0, 1023);	//3 da mecatronica PA2 (ok)
		legs[4] = new Dynamixel(&huart3, 0, 512, 0, 1023);	//4 da mecatronica PD8 <- n ligou // mudou pra AX(ok)
		legs[2] = new Dynamixel(&huart6, 0, 513, 0, 4095);	//2 da mecatronica PC6 <- mau contato
		legs[6] = new Dynamixel(&huart1, 1, 977, 0, 1023);	//6 da mecatronica PB6 (ok)
		legs[8] = new Dynamixel(&huart2, 1, 667, 0, 1023);	//8 da mecatronica PA2 (ok)
		legs[7] = new Dynamixel(&huart3, 1, 220, 0, 1023);	//7 da mecatronica PD8 // mudou pra AX (ok)
		legs[1] = new Dynamixel(&huart6, 1, 667, 0, 1023);	//1 da mecatronica PC6  <- mau contato (ok)
		legs[10] = new Dynamixel(&huart1, 2, 357, 0, 1023);	//10 da mecatronica PB6 (ok)
		legs[11] = new Dynamixel(&huart2, 2, 667, 256, 1023); //11 da mecatronica PA2 (ok)
		legs[0] = new Dynamixel(&huart3, 2, 513, 256, 1023);	//(ok)0 da mecatronica PD8 // olhando o robô de frente, começa na perna esquerda de baixo pra cima
		legs[9] = new Dynamixel(&huart6, 2, 2048, 0, 4095);	//9 da mecatronica PC6 <- mau contato
	}
//como saber qual pino da placa plugar os motores UART: apenas veja qual tipo de UART está ligado na discovery
// em seguida siga o caminho físico do fio que se parte em outros 3, ache o data desses 3 fios e ligue os motores conforme
// o código que está acima, por exemplo, se vc notou que o PB6(UART 1) está ligado nos outros 3 fios então os fios que seguem
//serão datas com UART 1, dessa maneira, olhe no código quais motores tem huart1, que seriam os 5,6,10 e eles podem ser ligados em
//qualquer ordem.

void Robot::init(){
#ifdef POSTE

#else
#ifdef SETID //se tiver dúvida olhe o comentário do defines
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
	for (int i=2; i<6; i++){
		legs[i]->setId(id);
		//legs[i]->setConfig();  //reseta sempre os motores de id 1
	}
	error((errorTypeDef)15);	//Pisca todos os leds para avisar que gravou
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
#endif
}

void Robot::controlCallback(){
#ifdef POSTE
	if(batteryVoltage() < VOLTAGE_LOW){
		//Rotina para desligar os motores (pode ser no erro também)
		error(ERR_LOW_BATTERY);
	}
	switch(desiredStep){
	case STEP_FORWARD:
		break;
	case STEP_LEFT:
		break;
	case STEP_RIGHT:
		break;
	case STEP_STOP:
		break;
	}
#else
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
#endif
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
