#include "timer_config.h"

void start_TIM4() {
  RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
  TIM4->CR1 |= 1;
  TIM4->PSC |= 84;
  TIM4->ARR |= 65000;
}

uint16_t read_TIM4() {
  return TIM4->CNT;
}

void delay_us (uint16_t micros) {
	TIM4->CNT = 0;  // set counter register value = 0
	while (read_TIM4() < micros);  // wait for the counter to reach the microsec input in the parameter
}