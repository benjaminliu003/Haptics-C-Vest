#include "servo_config.h"
#include "timer_config.h"
#include "ece198.h"

#include <stdbool.h>
#include <stdio.h>

void poke_user(GPIO_TypeDef *Port_Letter, uint16_t Pin_Trig, uint16_t dist_got, uint16_t timer_num, uint16_t channel){
    #define SER_PORT Port_Letter
    #define SER_TRIG Pin_Trig

    if (timer_num == 2){
        if (channel == 1){
            start_TIM2(1);
        }
        else if (channel == 2){
            start_TIM2(2);
        }
        else if (channel == 3){
            start_TIM2(3);
        }
        else if (channel == 4){
            start_TIM2(4);
        }
        InitializePin(SER_PORT, SER_TRIG, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_AF1_TIM2);
    }
    else if (timer_num == 3){
        if (channel == 1){
            start_TIM2(1);
        }
        else if (channel == 2){
            start_TIM2(2);
        }
        else if (channel == 3){
            start_TIM2(3);
        }
        else if (channel == 4){
            start_TIM2(4);
        }
        InitializePin(SER_PORT, SER_TRIG, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_AF2_TIM3);
    }

    double to_set = (dist_got * (-150.0/397.0)) + 500.0;
    int16_t set_this = to_set;
    TIM2->CCR1 = set_this;

    HAL_Delay(100);

    HAL_GPIO_DeInit(SER_PORT, SER_TRIG);
}