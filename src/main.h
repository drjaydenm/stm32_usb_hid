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

#include "usbd_core.h"
#include "usbd_desc.h"

#include "gpio_pin.h"

void SetupGPIO();
void SystemClockConfig(void);

USBD_HandleTypeDef USBD_Device;

GPIOPin scanRows[] =
{
    { GPIOA, GPIO_PIN_0 },
    { GPIOA, GPIO_PIN_1 },
    { GPIOA, GPIO_PIN_3 },
    { GPIOA, GPIO_PIN_4 },
};
int scanRowsCount = sizeof(scanRows) / sizeof(scanRows[0]);

GPIOPin statusLeds[] =
{
    { GPIOF, GPIO_PIN_0 },
    { GPIOF, GPIO_PIN_1 },
    { GPIOA, GPIO_PIN_8 },
    { GPIOB, GPIO_PIN_5 },
};
int statusLedsCount = sizeof(statusLeds) / sizeof(statusLeds[0]);

#endif