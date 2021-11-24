#include "servo_config.h"
#include "timer_config.h"
#include "ece198.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void poke_user(GPIO_TypeDef *Port_Letter, uint16_t Pin_Trig, uint16_t dist_got){
    #define SER_PORT Port_Letter
    #define SER_TRIG Pin_Trig

    InitializePin(GPIOA, SER_TRIG, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_AF1_TIM2);

    double to_set = (dist_got * (150.0/397.0)) + 350.0;
    int16_t set_this = to_set;
    TIM2->CCR1 = set_this;

    HAL_Delay(100);

    DeInitPin(SER_PORT, SER_TRIG);
}

void DeInitPin(GPIO_TypeDef *Port_Letter, uint16_t pins){
    GPIO_InitTypeDef GPIO_DeInit;
    GPIO_DeInit.Pin = pins;
    HAL_GPIO_DeInit(Port_Letter, &GPIO_DeInit);
}