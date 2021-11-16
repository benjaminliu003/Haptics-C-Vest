//#define ULTRA_TEST
#define SERVO_TEST

#include <stdbool.h> // booleans, i.e. true and false
#include <stdio.h>   // sprintf() function
#include <stdlib.h>  // srand() and random() functions

#include "ece198.h"

void start_TIM4() {
  RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
  TIM4->CR1 |= 1;
  TIM4->PSC |= 84-1;
}

void start_TIM3() { //for servo
  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
  TIM3->CR1 |= 1;
  TIM3->PSC |= 84-1;
  //TIM3->ARR = 20000;
}

uint16_t read_TIM4() { //for ultrasonic
  return TIM4->CNT;
}

uint16_t read_TIM3() { //for servo
  return TIM3->CNT;
}

int main(void)
{
    HAL_Init(); // initialize the Hardware Abstraction Layer

    // Peripherals (including GPIOs) are disabled by default to save power, so we
    // use the Reset and Clock Control registers to enable the GPIO peripherals that we're using.

    __HAL_RCC_GPIOA_CLK_ENABLE(); // enable port A (for the on-board LED, for example)
    __HAL_RCC_GPIOB_CLK_ENABLE(); // enable port B (for the rotary encoder inputs, for example)
    __HAL_RCC_GPIOC_CLK_ENABLE(); // enable port C (for the on-board blue pushbutton, for example)

    // initialize the pins to be input, output, alternate function, etc...

    InitializePin(GPIOA, GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // on-board LED

    // note: the on-board pushbutton is fine with the default values (no internal pull-up resistor
    // is required, since there's one on the board)

    // USE THIS FOR TESTING THE ULTRASONIC SENSOR AND PINOUTS - No touchie touchie
    // Timer init

    // PINS FOR THE ULTRASONIC SENSOR - THIS WAS A PAIN TO GET
    InitializePin(GPIOA, GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOA, GPIO_PIN_11, GPIO_MODE_INPUT, GPIO_NOPULL, 0);

    //InitializePin(GPIOA, GPIO_PIN_13, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);

    // set up for serial communication to the host computer
    // (anything we write to the serial port will appear in the terminal (i.e. serial monitor) in VSCode)

    SerialSetup(9600);

    HAL_Delay(4500);

    SerialPuts("Yo board is live. \n");

    // as mentioned above, only one of the following code sections will be used
    // (depending on which of the #define statements at the top of this file has been uncommented)

#ifdef ULTRA_TEST
    #define SEN_TRIG GPIO_PIN_6
    #define SEN_ECHO GPIO_PIN_11

    // Hey HAL 9000, is it time to check the time?
    bool state, rec_strt, found;
    state = false;
    rec_strt = false;
    found = false;

    // Bois, how far have we gone?
    uint16_t iters;
    double distance;
    iters = 1;
    distance = 0.0;

    // It is exactly [time] o'clock! bUt is it time for use to grab dist?
    uint32_t time, time1, waitTime, bruhTime, yesTime, recTime;
    time = 0;
    time1 = 0;
    bruhTime = 0;
    yesTime = 0;
    recTime = 0;
    waitTime = 0;


    while (true){                                  // May need to configure clock to les than milliescond
        uint16_t see1;
        see1 = 0;
        see1 = read_TIM4();

        char try1[1000];
        sprintf(try1, "usec time: %u \n", see1);
        SerialPuts(try1);

        if(state == false){
            time = HAL_GetTick();                   // update this as well to keep trying to obtain 10 usec?
            state = true;
            char howLong[1000];
            sprintf(howLong, "When First: %lu \n", time);
            SerialPuts(howLong);

            SerialPuts("Got initial time. \n");
        }
        if ((time1 - time) >= 10){
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, false);
            state = false;

            //add wait time and then time to grab dist?
            waitTime = HAL_GetTick();
            SerialPuts("Got first wait time. \n");

            while (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11)){
                bruhTime = HAL_GetTick();
                if ((bruhTime - waitTime) >= 9900){
                    //ha, sensor borked
                    SerialPuts("uh oh, sensor no workie! \n");
                }
            }
            while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11)){
                if(rec_strt == false){
                    recTime = HAL_GetTick();
                    rec_strt = true;
                    SerialPuts("Recording time is got. \n");
                }
                yesTime = HAL_GetTick() - recTime;
                
                distance = yesTime /* divide yesTime by some const given timer */;

                found = true;
                SerialPuts("Found the distance. \n");
            }
            if (found == true){
                char ret[100];
                sprintf(ret, "distance: %f \n", distance);
                SerialPuts(ret);
            }
        }
        else{
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, true);
            time1 = HAL_GetTick();
            SerialPuts("Getting time1. \n");
        }
        char howMany[1000];
        sprintf(howMany, "cycle: %u \n", iters);
        SerialPuts(howMany);

        ++iters;
        rec_strt = false;
        SerialPuts("Iteration. \n");
    }

#endif

#ifdef SERVO_TEST
    #define SIGNAL GPIO_PIN_13

    uint16_t pulse_begin, pulse_now;

    while(true){

        char ret[100];
        sprintf(ret, "value: %d \n", read_TIM4());
        SerialPuts(ret);

        
 
        if(read_TIM3() <= 1500){
            HAL_GPIO_WritePin(GPIOA, SIGNAL, true);

            // char ret[100];
            // sprintf(ret, "High: %d \n", read_TIM3());
            // SerialPuts(ret);

            //SerialPuts("High \n");
            //SerialPuts(read_TIM3()+'0');

        } else{
            HAL_GPIO_WritePin(GPIOA, SIGNAL, false);
            SerialPuts("Low \n");
        }
    }

#endif

    return 0;
}



// This function is called by the HAL once every millisecond
void SysTick_Handler(void)
{
    HAL_IncTick(); // tell HAL that a new tick has happened
    // we can do other things in here too if we need to, but be careful
}
