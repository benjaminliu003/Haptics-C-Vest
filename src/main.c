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
    
    uint16_t i = 0;

    while (true){
        if (i == 0){
            uint16_t ranged = find_range(GPIOC, GPIOC, GPIO_PIN_0, GPIO_PIN_3);
            debug_poke(i, ranged);
            ++i;
            char err1[1000];
            sprintf(err1, "First \n");
            SerialPuts(err1);
        }
        else if (i == 1){
            uint16_t ranged = find_range(GPIOC, GPIOC, GPIO_PIN_1, GPIO_PIN_2);
            debug_poke(i, ranged);
            ++i;
        }
        else if (i == 2){
            uint16_t ranged = find_range(GPIOA, GPIOH, GPIO_PIN_4, GPIO_PIN_1);
            debug_poke(i, ranged);
            ++i;
        }
        else if (i == 3){
            uint16_t ranged = find_range(GPIOC, GPIOC, GPIO_PIN_10, GPIO_PIN_11);
            debug_poke(i, ranged);
            ++i;
        }
        else if (i == 4){
            uint16_t ranged = find_range(GPIOD, GPIOC, GPIO_PIN_2, GPIO_PIN_12);
            debug_poke(i, ranged);
            ++i;
        }
        else if (i == 5){
            uint16_t ranged = find_range(GPIOA, GPIOA, GPIO_PIN_13, GPIO_PIN_14);
            debug_poke(i, ranged);
            ++i;
        }
        else if (i == 6){
            uint16_t ranged = find_range(GPIOC, GPIOH, GPIO_PIN_15, GPIO_PIN_0);
            debug_poke(i, ranged);
            ++i;
        }
        else if (i == 7){
            uint16_t ranged = find_range(GPIOA, GPIOC, GPIO_PIN_15, GPIO_PIN_14);
            debug_poke(i, ranged);
            ++i;
        }
        else if (i == 8){
            uint16_t ranged = find_range(GPIOB, GPIOB, GPIO_PIN_13, GPIO_PIN_5);
            debug_poke(i, ranged);
            i = 0;
            char err1[1000];
            sprintf(err1, "Last \n");
            SerialPuts(err1);
        }        
    }
    
#endif
    return 0;
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}