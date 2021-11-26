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

void servo_TIM2(GPIO_TypeDef *Port_Letter, uint16_t Pin_Trig, uint32_t channel, uint16_t range) {
  double to_set = (range * (-150.0/397.0)) + 500.0;
  int32_t set_this = to_set;

  uint16_t period = 20000, prescale = 84;
  __TIM3_CLK_ENABLE();  // enable timer 3
  TIM_HandleTypeDef pwmTimerInstance2;  // this variable stores an instance of the timer
  InitializePWMTimer(&pwmTimerInstance2, TIM2, period, prescale);   // initialize the timer instance
  InitializePWMChannel(&pwmTimerInstance2, channel);
  InitializePin(Port_Letter, Pin_Trig, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_AF1_TIM2);
  SetPWMDutyCycle(&pwmTimerInstance2, channel, set_this);
}

void servo_TIM3(GPIO_TypeDef *Port_Letter, uint16_t Pin_Trig, uint32_t channel, uint16_t range) {
  double to_set = (range * (-150.0/397.0)) + 500.0;
  int32_t set_this = to_set;

  uint16_t period = 20000, prescale = 84;
  __TIM3_CLK_ENABLE();  // enable timer 3
  TIM_HandleTypeDef pwmTimerInstance2;  // this variable stores an instance of the timer
  InitializePWMTimer(&pwmTimerInstance2, TIM3, period, prescale);   // initialize the timer instance
  InitializePWMChannel(&pwmTimerInstance2, channel);
  InitializePin(Port_Letter, Pin_Trig, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_AF2_TIM3);
  SetPWMDutyCycle(&pwmTimerInstance2, channel, set_this);
}

uint16_t read_TIM4() {
  return TIM4->CNT;
}

void delay_us (uint16_t micros) {
	TIM4->CNT = 0;  // set counter register value = 0
	while (read_TIM4() < micros);  // wait for the counter to reach the microsec input in the parameter
}