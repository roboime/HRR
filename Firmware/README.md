# HRR 2022
## Firmware

### Função

Controlar os motores AX-12A e MX-28T das pernas do robô por protocolo UART half duplex e controlar os motores MG90s dos braços por PWM.

### Features a serem implementados

- [x] Colocar código para rodar no STM32
- [x] Controle dos motores das pernas
- [ ] Feedback dos motores das pernas
- [ ] Controle dos motores dos braços
- [x] Leitura do CSV da mecatrônica
- [x] Diferentes tipos de passos
- [x] Comunicação com inteligência
- [ ] Comunicação RF para telemetria
- [ ] Interface gráfica no computador para telemetria
- [ ] Acelerômetro para detecção e tratamento de quedas
- [x] Medição de carga da bateria e desligamento em carga baixa
- [ ] Gravação de log no cartão de memória

### Periféricos e pinos

| Periférico            | Pino MCU  | Função                        |
| --------------------- | --------- | ----------------------------- |
| TIM3 CHANNEL 1        | PB4       | PWM servo do braço            |
| TIM3 CHANNEL 2        | PC7       | PWM servo do braço            |
| TIM3 CHANNEL 3        | PB0       | PWM servo do braço            |
| TIM3 CHANNEL 4        | PB1       | PWM servo do braço            |
| TIM4 CHANNEL 3        | PB8       | PWM servo do braço            |
| TIM4 CHANNEL 4        | PB9       | PWM servo do braço            |
| TIM6                  |           | Interrupção de controle       |
| ADC1 IN1              | PA1       | Medidor de carga da bateria   |
| SDIO D0               | PC8       | Cartão de memória             |
| SDIO CK               | PC12      | Cartão de memória             |
| SDIO CMD              | PD2       | Cartão de memória             |
| SDIO DETECT           | PC9       | Cartão de memória             |
| UART4 TX              | PC10      | Comunicação com Raspberry Pi  |
| UART4 RX              | PC11      | Comunicação com Raspberry Pi  |
| USART1                | PB6       | Servos da perna               |
| USART2                | PA2       | Servos da perna               |
| USART3                | PD8       | Servos da perna               |
| USART6                | PC6       | Servos da perna               |