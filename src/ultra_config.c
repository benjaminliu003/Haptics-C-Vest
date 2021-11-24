#include "ultra_config.h"
#include "timer_config.h"
#include "ece198.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

uint16_t find_range(GPIO_TypeDef *Port_Letter, uint16_t Pin_Trig, uint16_t Pin_Echo){
    #define SEN_TRIG Pin_Trig
    #define SEN_ECHO Pin_Echo

    uint16_t micros_trig, read_len;
    micros_trig = 10;

    read_len = 0;
    bool started = false;

    HAL_GPIO_TogglePin(Port_Letter,SEN_TRIG);
    delay_us(micros_trig);
    HAL_GPIO_TogglePin(Port_Letter,SEN_TRIG);

    while (!HAL_GPIO_ReadPin(Port_Letter, SEN_ECHO));      //32613?
    while (HAL_GPIO_ReadPin(Port_Letter, SEN_ECHO)){
        if (started == false){
            TIM4->CNT = 0;
            started = true;
        }
        read_len = read_TIM4();
    }
    if(started == true){
        if ((read_len < 150) || ((read_len < 37500) && (read_len > 25000)) || (read_len > 38500)){
            char try2[100];
            sprintf(try2, "Noise \n");
            SerialPuts(try2);
            return 0;
        }
        else if ((read_len > 37500) && (read_len < 38500)){
            char try3[100];
            sprintf(try3, "No Obstacle \n");
            SerialPuts(try3);
            return 1;
        }
        else if ((read_len > 149) && (read_len < 25001)){
            double rang = (read_len * 3.43) / 34.3;
            uint16_t rng = rang;
            
            if (rng > 400){
                char try5[1000];
                sprintf(try5, "Too Far! \n");
                SerialPuts(try5);
                return 0;
            }

            char try4[1000];
            sprintf(try4, "Range of: %u cm \n", rng);
            SerialPuts(try4);
            return rng;
        }  // set up system to compare current and last measrement, if change drastic, ignore.
        return 0;
    }
    return 0;
}