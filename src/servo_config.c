#include "servo_config.h"
#include "timer_config.h"
#include "ece198.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void poke_user(GPIO_TypeDef *Port_Letter, uint16_t Pin_Trig, uint16_t dist_got){
    #define SER_TRIG Pin_Trig
    
    //hmmmmm, must me between 1 to 1.3 microsecs
    uint16_t active_delay = dist_got * 9;
    char err2[1000];
    sprintf(err2, "deploy time: %u \n", active_delay);
    SerialPuts(err2);
    uint16_t pulse_delay = 20 - active_delay;

    if ((active_delay < 1300) && (active_delay > 999)){
        HAL_GPIO_TogglePin(Port_Letter,SER_TRIG);
        HAL_Delay(active_delay);
        HAL_GPIO_TogglePin(Port_Letter,SER_TRIG);
        HAL_Delay(pulse_delay);
    }
}