#ifndef __GPIO_PIN_H
#define __GPIO_PIN_H

#ifdef MCU_CLASS_F0
    #include "stm32f0xx_hal_gpio.h"
#elif MCU_CLASS_L0
    #include "stm32l0xx_hal_gpio.h"
#endif

typedef struct
{
    GPIO_TypeDef* Port;
    uint16_t Pin;
} GPIOPin;

#endif