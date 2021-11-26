#include "stm32f4xx_hal.h"

void poke_user(GPIO_TypeDef *Port_Letter, uint16_t Pin_Trig, uint16_t dist_got, uint16_t timer_num, uint16_t channel);
void DeInitPin(GPIO_TypeDef *port, uint16_t pins);