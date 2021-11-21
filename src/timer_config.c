#include "timer_config.h"

void start_TIM4() {
  RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
  TIM4->CR1 |= 1;
  TIM4->PSC |= 84;
  TIM4->ARR |= 65000;
  TIM4->CNT = 0;
}

void start_TIM3() {
  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
  TIM3->CR1 |= 1;
  TIM3->PSC |= 84;
  TIM3->ARR |= 65000;
  TIM3->CNT = 0;
}

uint16_t read_TIM4() {
  return TIM4->CNT;
}

uint16_t read_TIM3() {
  return TIM3->CNT;
}

void delay_us (uint16_t micros) {
	TIM4->CNT = 0;  // set counter register value = 0
	while (read_TIM4() < micros);  // wait for the counter to reach the microsec input in the parameter
}

/*
void read_in (GPIO_TypeDef *port, uint16_t pin_num){
    port.Pin = pin_num;
}*/