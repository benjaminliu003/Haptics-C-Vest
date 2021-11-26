//First, we have to include the prerequisites of the program.
#include <stdbool.h> // booleans, i.e. true and false
#include <stdio.h>   // sprintf() function
#include <stdlib.h>  // srand() and random() functions

//We will also include files containing our support functions and other code
#include "ece198.h"
#include "timer_config.h"
#include "ultra_config.h"

#define RUNTIME

void debug_poke (uint16_t i, uint16_t range){
    if (range == 0){
            char err1[1000];
            sprintf(err1, "BAD READ \n");
            SerialPuts(err1);
    }
    else if (range == 1){
        char wut[1000];
        sprintf(wut, "NO OBSTACLE \n");
        SerialPuts(wut);
    }
    else{

        //PWM statements provided by Bernie Roehl
        if (i == 0){
            double to_set = (range * (-150.0/397.0)) + 500.0;
            int32_t set_this = to_set;

            uint16_t period = 20000, prescale = 84;
            __TIM3_CLK_ENABLE();  // enable timer 3
            TIM_HandleTypeDef pwmTimerInstance2;  // this variable stores an instance of the timer
            InitializePWMTimer(&pwmTimerInstance2, TIM3, period, prescale);   // initialize the timer instance
            InitializePWMChannel(&pwmTimerInstance2, TIM_CHANNEL_4);
            InitializePin(GPIOC, GPIO_PIN_9, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_AF2_TIM3);
            SetPWMDutyCycle(&pwmTimerInstance2, TIM_CHANNEL_4, set_this);

        }
        else if (i == 1){
            double to_set = (range * (-150.0/397.0)) + 500.0;
            int32_t set_this = to_set;

            uint16_t period = 20000, prescale = 84;
            __TIM3_CLK_ENABLE();  // enable timer 3
            TIM_HandleTypeDef pwmTimerInstance2;  // this variable stores an instance of the timer
            InitializePWMTimer(&pwmTimerInstance2, TIM3, period, prescale);   // initialize the timer instance
            InitializePWMChannel(&pwmTimerInstance2, TIM_CHANNEL_3);
            InitializePin(GPIOC, GPIO_PIN_8, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_AF2_TIM3);
            SetPWMDutyCycle(&pwmTimerInstance2, TIM_CHANNEL_3, set_this);

        }
        else if (i == 2){
            double to_set = (range * (-150.0/397.0)) + 500.0;
            int32_t set_this = to_set;

            uint16_t period = 20000, prescale = 84;
            __TIM2_CLK_ENABLE();  // enable timer 2
            TIM_HandleTypeDef pwmTimerInstance2;  // this variable stores an instance of the timer
            InitializePWMTimer(&pwmTimerInstance2, TIM2, period, prescale);   // initialize the timer instance
            InitializePWMChannel(&pwmTimerInstance2, TIM_CHANNEL_2);
            InitializePin(GPIOB, GPIO_PIN_3, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_AF1_TIM2);
            SetPWMDutyCycle(&pwmTimerInstance2, TIM_CHANNEL_2, set_this);

        }
        else if (i == 3){
            double to_set = (range * (-150.0/397.0)) + 500.0;
            int32_t set_this = to_set;

            uint16_t period = 20000, prescale = 84;
            __TIM3_CLK_ENABLE();  // enable timer 3
            TIM_HandleTypeDef pwmTimerInstance2;  // this variable stores an instance of the timer
            InitializePWMTimer(&pwmTimerInstance2, TIM3, period, prescale);   // initialize the timer instance
            InitializePWMChannel(&pwmTimerInstance2, TIM_CHANNEL_1);
            InitializePin(GPIOC, GPIO_PIN_6, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_AF2_TIM3);
            SetPWMDutyCycle(&pwmTimerInstance2, TIM_CHANNEL_1, set_this);

        }
        else if (i == 4){
            double to_set = (range * (-150.0/397.0)) + 500.0;
            int32_t set_this = to_set;

            uint16_t period = 20000, prescale = 84;
            __TIM2_CLK_ENABLE();  // enable timer 2
            TIM_HandleTypeDef pwmTimerInstance2;  // this variable stores an instance of the timer
            InitializePWMTimer(&pwmTimerInstance2, TIM2, period, prescale);   // initialize the timer instance
            InitializePWMChannel(&pwmTimerInstance2, TIM_CHANNEL_2);
            InitializePin(GPIOA, GPIO_PIN_1, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_AF1_TIM2);
            SetPWMDutyCycle(&pwmTimerInstance2, TIM_CHANNEL_2, set_this);

        }
        else if (i == 5){
            double to_set = (range * (-150.0/397.0)) + 500.0;
            int32_t set_this = to_set;

            uint16_t period = 20000, prescale = 84;
            __TIM3_CLK_ENABLE();  // enable timer 3
            TIM_HandleTypeDef pwmTimerInstance2;  // this variable stores an instance of the timer
            InitializePWMTimer(&pwmTimerInstance2, TIM3, period, prescale);   // initialize the timer instance
            InitializePWMChannel(&pwmTimerInstance2, TIM_CHANNEL_2);
            InitializePin(GPIOC, GPIO_PIN_7, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_AF2_TIM3);
            SetPWMDutyCycle(&pwmTimerInstance2, TIM_CHANNEL_2, set_this);

        }
        else if (i == 6){
            double to_set = (range * (-150.0/397.0)) + 500.0;
            int32_t set_this = to_set;

            uint16_t period = 20000, prescale = 84;
            __TIM2_CLK_ENABLE();  // enable timer 2
            TIM_HandleTypeDef pwmTimerInstance2;  // this variable stores an instance of the timer
            InitializePWMTimer(&pwmTimerInstance2, TIM2, period, prescale);   // initialize the timer instance
            InitializePWMChannel(&pwmTimerInstance2, TIM_CHANNEL_1);
            InitializePin(GPIOA, GPIO_PIN_15, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_AF1_TIM2);
            SetPWMDutyCycle(&pwmTimerInstance2, TIM_CHANNEL_1, set_this);

        }
        else if (i == 7){
            double to_set = (range * (-150.0/397.0)) + 500.0;
            int32_t set_this = to_set;

            uint16_t period = 20000, prescale = 84;
            __TIM2_CLK_ENABLE();  // enable timer 3
            TIM_HandleTypeDef pwmTimerInstance2;  // this variable stores an instance of the timer
            InitializePWMTimer(&pwmTimerInstance2, TIM2, period, prescale);   // initialize the timer instance
            InitializePWMChannel(&pwmTimerInstance2, TIM_CHANNEL_1);
            InitializePin(GPIOA, GPIO_PIN_5, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_AF1_TIM2);
            SetPWMDutyCycle(&pwmTimerInstance2, TIM_CHANNEL_1, set_this);

        }
        else if (i == 8){
            double to_set = (range * (-150.0/397.0)) + 500.0;
            int32_t set_this = to_set;

            uint16_t period = 20000, prescale = 84;
            __TIM3_CLK_ENABLE();  // enable timer 3
            TIM_HandleTypeDef pwmTimerInstance2;  // this variable stores an instance of the timer
            InitializePWMTimer(&pwmTimerInstance2, TIM3, period, prescale);   // initialize the timer instance
            InitializePWMChannel(&pwmTimerInstance2, TIM_CHANNEL_1);
            InitializePin(GPIOA, GPIO_PIN_6, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_AF2_TIM3);
            SetPWMDutyCycle(&pwmTimerInstance2, TIM_CHANNEL_1, set_this);

        }
    }
}

int main(void)
{
    HAL_Init(); // initialize the Hardware Abstraction Layer

    // Peripherals (including GPIOs) are disabled by default to save power, so we
    // use the Reset and Clock Control registers to enable the GPIO peripherals that we're using.

    __HAL_RCC_GPIOA_CLK_ENABLE(); // enable port A (for the on-board LED, for example)
    __HAL_RCC_GPIOB_CLK_ENABLE(); // enable port B (for the rotary encoder inputs, for example)
    __HAL_RCC_GPIOC_CLK_ENABLE(); // enable port C (for the on-board blue pushbutton, for example)
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();

    // initialize the pins to be input, output, alternate function, etc...

    InitializePin(GPIOA, GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // on-board LED

    // set up for serial communication to the host computer
    // (anything we write to the serial port will appear in the terminal (i.e. serial monitor) in VSCode)

    SerialSetup(9600);
    HAL_Delay(4500);
    SerialPuts("Board is live. \n");

    start_TIM4();
    //start_TIM2();

#ifdef RUNTIME
    
    
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
            char err1[1000];
            sprintf(err1, "Second \n");
            SerialPuts(err1);
        }
        else if (i == 2){
            uint16_t ranged = find_range(GPIOA, GPIOH, GPIO_PIN_4, GPIO_PIN_1);
            debug_poke(i, ranged);
            ++i;
            char err1[1000];
            sprintf(err1, "Third \n");
            SerialPuts(err1);
        }
        else if (i == 3){
            uint16_t ranged = find_range(GPIOB, GPIOA, GPIO_PIN_12, GPIO_PIN_7);
            debug_poke(i, ranged);
            ++i;
            char err1[1000];
            sprintf(err1, "Fourth \n");
            SerialPuts(err1);
        }
        else if (i == 4){
            uint16_t ranged = find_range(GPIOB, GPIOA, GPIO_PIN_1, GPIO_PIN_8);
            debug_poke(i, ranged);
            ++i;
            char err1[1000];
            sprintf(err1, "Fifth \n");
            SerialPuts(err1);
        }
        else if (i == 5){
            uint16_t ranged = find_range(GPIOC, GPIOB, GPIO_PIN_5, GPIO_PIN_9);
            debug_poke(i, ranged);
            ++i;
            char err1[1000];
            sprintf(err1, "Sixth \n");
            SerialPuts(err1);
        }
        else if (i == 6){
            uint16_t ranged = find_range(GPIOA, GPIOA, GPIO_PIN_13, GPIO_PIN_14);
            debug_poke(i, ranged);
            ++i;
            char err1[1000];
            sprintf(err1, "Seventh \n");
            SerialPuts(err1);
        }
        else if (i == 7){
            uint16_t ranged = find_range(GPIOB, GPIOB, GPIO_PIN_15, GPIO_PIN_10);
            debug_poke(i, ranged);
            ++i;
            char err1[1000];
            sprintf(err1, "Eigth \n");
            SerialPuts(err1);
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