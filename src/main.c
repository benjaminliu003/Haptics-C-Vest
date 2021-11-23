#include <stdbool.h> // booleans, i.e. true and false
#include <stdio.h>   // sprintf() function
#include <stdlib.h>  // srand() and random() functions

#include "ece198.h"
#include "timer_config.h"

// if return 1 - no obstacle, if return 0 - error, if return other - good read
#include "ultra_config.h"
#include "servo_config.h"

#define RUNTIME

int main(void)
{
    HAL_Init(); // initialize the Hardware Abstraction Layer

    // Peripherals (including GPIOs) are disabled by default to save power, so we
    // use the Reset and Clock Control registers to enable the GPIO peripherals that we're using.

    __HAL_RCC_GPIOA_CLK_ENABLE(); // enable port A (for the on-board LED, for example)
    __HAL_RCC_GPIOB_CLK_ENABLE(); // enable port B (for the rotary encoder inputs, for example)
    __HAL_RCC_GPIOC_CLK_ENABLE(); // enable port C (for the on-board blue pushbutton, for example)

    //__HAL_RCC_TIM4_CLK_ENABLE();

    // initialize the pins to be input, output, alternate function, etc...

    InitializePin(GPIOA, GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // on-board LED

    // note: the on-board pushbutton is fine with the default values (no internal pull-up resistor
    // is required, since there's one on the board)

    // USE THIS FOR TESTING THE ULTRASONIC SENSOR AND PINOUTS - No touchie touchie
    // Timer init

    // PINS FOR THE ULTRASONIC SENSOR - THIS WAS A PAIN TO GET
    InitializePin(GPIOA, GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOA, GPIO_PIN_11, GPIO_MODE_INPUT, GPIO_NOPULL, 0);

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0);

    // set up for serial communication to the host computer
    // (anything we write to the serial port will appear in the terminal (i.e. serial monitor) in VSCode)

    SerialSetup(9600);

    HAL_Delay(4500);

    SerialPuts("Yo board is live. \n");

    start_TIM4();

    // as mentioned above, only one of the following code sections will be used
    // (depending on which of the #define statements at the top of this file has been uncommented)

#ifdef RUNTIME
    start_TIM2();
    InitializePin(GPIOA, GPIO_PIN_13, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_AF1_TIM2);
    
    while (true){
        TIM2->CCR1 = 25;
        HAL_Delay(2000);
        TIM2->CCR1 = 75;
        HAL_Delay(2000);
        TIM2->CCR1 = 125;
        HAL_Delay(2000);
    }

    /*
    while (true){
        uint16_t ranged = find_range(GPIOA, GPIO_PIN_6, GPIO_PIN_11);
        if (ranged == 0){
            char err1[1000];
            sprintf(err1, "READ ERROR \n");
            SerialPuts(err1);
        }
        else if (ranged == 1){
            char wut[1000];
            sprintf(wut, "NO OBSTACLE \n");
            SerialPuts(wut);
        }else{
            poke_user(GPIOA, GPIO_PIN_13, ranged);
        }
    }*/
    
#endif

    return 0;
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}