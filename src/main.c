#include <stdbool.h> // booleans, i.e. true and false
#include <stdio.h>   // sprintf() function

#include "ece198.h"
#include "timer_config.h"
// if return 1 - no obstacle, if return 0 - error, if return other - good read
#include "ultra_config.h"
#include "servo_config.h"

#define RUNTIME

void debug_poke (uint16_t i, uint16_t range){
    if (range == 0){
            char err1[1000];
            sprintf(err1, "READ ERROR \n");
            SerialPuts(err1);
    }
    else if (range == 1){
        char wut[1000];
        sprintf(wut, "NO OBSTACLE \n");
        SerialPuts(wut);
    }
    else{ //REMEBER TO PUT IN NEW PINS ONCE PLUGGED IN
        if (i == 0){
            poke_user(GPIOA, GPIO_PIN_15, range);
        }
        else if (i == 1){
            poke_user(GPIOA, GPIO_PIN_15, range);
        }
        else if (i == 2){
            poke_user(GPIOA, GPIO_PIN_15, range);
        }
        else if (i == 3){
            poke_user(GPIOA, GPIO_PIN_15, range);
        }
        else if (i == 4){
            poke_user(GPIOA, GPIO_PIN_15, range);
        }
        else if (i == 5){
            poke_user(GPIOA, GPIO_PIN_15, range);
        }
        else if (i == 6){
            poke_user(GPIOA, GPIO_PIN_15, range);
        }
        else if (i == 7){
            poke_user(GPIOA, GPIO_PIN_15, range);
        }
        else if (i == 8){
            poke_user(GPIOA, GPIO_PIN_15, range);
        }
    }
}

int main(void)
{
    HAL_Init(); // initialize the Hardware Abstraction Layer

    __HAL_RCC_GPIOA_CLK_ENABLE(); // enable port A
    __HAL_RCC_GPIOB_CLK_ENABLE(); // enable port B
    __HAL_RCC_GPIOC_CLK_ENABLE(); // enable port C
    __HAL_RCC_GPIOD_CLK_ENABLE(); // enable port D
    __HAL_RCC_GPIOH_CLK_ENABLE(); // enable port H

    InitializePin(GPIOA, GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // on-board LED

    SerialSetup(9600);
    HAL_Delay(4500);
    SerialPuts("Board is live. \n");

    start_TIM4();
    start_TIM2();

#ifdef RUNTIME
    
    /*while (true){
        TIM2->CCR1 = 350; //lowest range
        HAL_Delay(2000);
        TIM2->CCR1 = 500; //highest range
        HAL_Delay(2000);
    }*/
    
    GPIO_TypeDef *Trigs[9] = {GPIOC, GPIOC, GPIOA, GPIOC, GPIOD, GPIOA, GPIOC, GPIOA, GPIOB};
    GPIO_TypeDef *Echos[9] = {GPIOC, GPIOC, GPIOH, GPIOC, GPIOC, GPIOA, GPIOH, GPIOC, GPIOB};
    uint16_t Trig_Pins[9] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_4, GPIO_PIN_10, GPIO_PIN_2, GPIO_PIN_13, GPIO_PIN_15, GPIO_PIN_15, GPIO_PIN_13};
    uint16_t Echo_Pins[9] = {GPIO_PIN_3, GPIO_PIN_2, GPIO_PIN_1, GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_14, GPIO_PIN_0, GPIO_PIN_14, GPIO_PIN_5};

    uint16_t i = 0;

    while (true){
        if (i != 8){
            uint16_t ranged = find_range(Trigs[i], Echos[i], Trig_Pins[i], Echo_Pins[i]);
            debug_poke(i, ranged);
            ++i;
            char err1[1000];
            sprintf(err1, "First \n");
            SerialPuts(err1);
        }
        if (i == 8){
            i = 0;
            char err2[1000];
            sprintf(err2, "Last \n");
            SerialPuts(err2);
        }        
    }
#endif
    return 0;
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}