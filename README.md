uint8_t uartBuf[64];
	uint8_t paramArray[2];  // contem os parametros de setar id
	uint8_t paramArray2[5];  // parametros da primeira posiçao
	uint8_t paramArray3[5];  // parametros da segunda posiçao
	uint8_t motorId;

  void sendInstruction(uint8_t instruction, uint8_t* paramArray, uint8_t numParams){
	  //while(huartptr->gState != HAL_UART_STATE_READY);	//Tem que implementar timeout
	  uartBuf[0] = 0xFF;				//Header
	  uartBuf[1] = 0xFF;				//Header
	  uartBuf[2] = motorId;				//ID
	  uartBuf[3] = numParams + 2;		//Length
	  uartBuf[4] = instruction;			//Instruction
	  uint8_t i;
	  uint8_t somaParams = 0;
	  for(i=0; i<numParams; i++){
		  uartBuf[i+5] = paramArray[i];	//Parameters
		  somaParams += paramArray[i];
	  }
	  uartBuf[i+5] = ~(motorId + numParams + 2 + instruction + somaParams);	//Checksum
	  HAL_UART_Transmit_DMA(&huart1, uartBuf, numParams + 6);  //tem q ficar mudando a porta aqui
}

	void main(){

	uint8_t novoId = 0x00;
  	  paramArray[0] = 0x03; 	//Starting adress da instruçao de ID
  	  paramArray[1] = novoId; 	//novo ID (se mudar tem q mudar o uartbuf2 do sendInstruction)
  	  motorId = 0xFE;  // ID de broadcast
  	  uint16_t pos1 = 1000;
  	  uint16_t pos2 = 500;
  	  uint16_t spd = 500;

  	  sendInstruction(0x03, paramArray, 2);  // set ID

  	  motorId = novoId;

  	  paramArray2[0] = 30;			//Goal position
  	  paramArray2[1] = pos1;		//Conferir endianess
  	  paramArray2[2] = pos1>>8;
  	  paramArray2[3] = spd;
  	  paramArray2[4] = spd>>8;

  	  paramArray3[0] = 30;			//Goal position
  	  paramArray3[1] = pos2;		//Conferir endianess
  	  paramArray3[2] = pos2>>8;
  	  paramArray3[3] = spd;
  	  paramArray3[4] = spd>>8;


}

  while (1)
  {
	  sendInstruction(0x03, paramArray2, 5);
	  HAL_Delay(2000);
	  sendInstruction(0x03, paramArray3, 5);
	  HAL_Delay(2000);
}
