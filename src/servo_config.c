#include "servo_config.h"
#include "timer_config.h"
#include "ece198.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void poke_user(GPIO_TypeDef *Port_Letter, uint16_t Pin_Trig, uint16_t dist_got){
    #define SER_TRIG Pin_Trig
    
    //hmmmmm, must me between 1 to 1.3 microsecs
    uint16_t active_delay = dist_got / 1.134;
    uint16_t pulse_delay = 20000 - active_delay;
    
    HAL_GPIO_TogglePin(Port_Letter,SER_TRIG);
    delay_us(active_delay);
    HAL_GPIO_TogglePin(Port_Letter,SER_TRIG);
    delay_us(pulse_delay);
}