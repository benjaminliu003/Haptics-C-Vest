#include "stm32f4xx_hal.h"

void start_TIM4();
void servo_TIM2(GPIO_TypeDef *Port_Letter, uint16_t Pin_Trig, uint32_t channel, uint16_t range);
void servo_TIM3(GPIO_TypeDef *Port_Letter, uint16_t Pin_Trig, uint32_t channel, uint16_t range);
uint16_t read_TIM4();
void delay_us (uint16_t micros);