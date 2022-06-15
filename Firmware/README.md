# HRR 2022
## Firmware

### Fun��o

Controlar os motores AX-12A e MX-28T das pernas do rob� por protocolo UART half duplex e controlar os motores MG90s dos bra�os por PWM.

### Features a serem implementados

- [x] Colocar c�digo para rodar no STM32
- [x] Controle dos motores das pernas
- [ ] Feedback dos motores das pernas
- [ ] Controle dos motores dos bra�os
- [x] Leitura do CSV da mecatr�nica
- [x] Diferentes tipos de passos
- [x] Comunica��o com intelig�ncia
- [ ] Comunica��o RF para telemetria
- [ ] Interface gr�fica no computador para telemetria
- [ ] Aceler�metro para detec��o e tratamento de quedas
- [x] Medi��o de carga da bateria e desligamento em carga baixa
- [ ] Grava��o de log no cart�o de mem�ria

### Perif�ricos e pinos

| Perif�rico            | Pino MCU  | Fun��o                        |
| --------------------- | --------- | ----------------------------- |
| TIM3 CHANNEL 1        | PB4       | PWM servo do bra�o            |
| TIM3 CHANNEL 2        | PC7       | PWM servo do bra�o            |
| TIM3 CHANNEL 3        | PB0       | PWM servo do bra�o            |
| TIM3 CHANNEL 4        | PB1       | PWM servo do bra�o            |
| TIM4 CHANNEL 3        | PB8       | PWM servo do bra�o            |
| TIM4 CHANNEL 4        | PB9       | PWM servo do bra�o            |
| TIM6                  |           | Interrup��o de controle       |
| ADC1 IN1              | PA1       | Medidor de carga da bateria   |
| SDIO D0               | PC8       | Cart�o de mem�ria             |
| SDIO CK               | PC12      | Cart�o de mem�ria             |
| SDIO CMD              | PD2       | Cart�o de mem�ria             |
| SDIO DETECT           | PC9       | Cart�o de mem�ria             |
| UART4 TX              | PC10      | Comunica��o com Raspberry Pi  |
| UART4 RX              | PC11      | Comunica��o com Raspberry Pi  |
| USART1                | PB6       | Servos da perna               |
| USART2                | PA2       | Servos da perna               |
| USART3                | PD8       | Servos da perna               |
| USART6                | PC6       | Servos da perna               |