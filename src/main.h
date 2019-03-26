#ifndef __MAIN_H
#define __MAIN_H

#include <stdint.h>

#ifdef MCU_CLASS_F0
    #include "stm32f0xx.h"
    #include "stm32f0xx_hal.h"
#elif MCU_CLASS_L0
    #include "stm32l0xx.h"
    #include "stm32l0xx_hal.h"
#endif

#include "gpio_pin.h"
#include "keyboard.h"

void SetupGPIO();
void SystemClockConfig(void);

GPIOPin statusLeds[] =
{
    { GPIOF, GPIO_PIN_0 },
    { GPIOF, GPIO_PIN_1 },
    { GPIOA, GPIO_PIN_8 },
    { GPIOB, GPIO_PIN_5 },
};
int statusLedsCount = sizeof(statusLeds) / sizeof(statusLeds[0]);

#endif