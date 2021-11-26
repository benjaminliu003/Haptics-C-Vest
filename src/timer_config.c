#include "timer_config.h"
#include "ece198.h"
#include "stm32f4xx_hal.h"

void start_TIM4() {
  RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
  TIM4->CR1 |= 1;
  TIM4->PSC |= 84;
  TIM4->ARR |= 65000;
  TIM4->CNT = 0;
}

void start_TIM2(uint16_t channel) {
  uint16_t period = 20000, prescale = 84;
  __TIM2_CLK_ENABLE();  // enable timer 2
  TIM_HandleTypeDef pwmTimerInstance;  // this variable stores an instance of the timer
  InitializePWMTimer(&pwmTimerInstance, TIM2, period, prescale);   // initialize the timer instance
  if (channel == 1){
    InitializePWMChannel(&pwmTimerInstance, TIM_CHANNEL_1);
  }
  else if (channel == 2){
    InitializePWMChannel(&pwmTimerInstance, TIM_CHANNEL_2);
  }
  else if (channel == 3){
    InitializePWMChannel(&pwmTimerInstance, TIM_CHANNEL_3);
  }
  else if (channel == 4){
    InitializePWMChannel(&pwmTimerInstance, TIM_CHANNEL_4);
  }
}

void start_TIM3(uint16_t channel) {
  uint16_t period = 20000, prescale = 84;
  __TIM3_CLK_ENABLE();  // enable timer 2
  TIM_HandleTypeDef pwmTimerInstance;  // this variable stores an instance of the timer
  InitializePWMTimer(&pwmTimerInstance, TIM3, period, prescale);   // initialize the timer instance
  if (channel == 1){
    InitializePWMChannel(&pwmTimerInstance, TIM_CHANNEL_1);
  }
  else if (channel == 2){
    InitializePWMChannel(&pwmTimerInstance, TIM_CHANNEL_2);
  }
  else if (channel == 3){
    InitializePWMChannel(&pwmTimerInstance, TIM_CHANNEL_3);
  }
  else if (channel == 4){
    InitializePWMChannel(&pwmTimerInstance, TIM_CHANNEL_4);
  }
}

uint16_t read_TIM4() {
  return TIM4->CNT;
}

uint16_t read_TIM2() {
  return TIM2->CNT;
}

void delay_us (uint16_t micros) {
	TIM4->CNT = 0;  // set counter register value = 0
	while (read_TIM4() < micros);  // wait for the counter to reach the microsec input in the parameter
}