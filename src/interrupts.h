#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include "stm32f0xx_hal.h"

void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void USB_IRQHandler(void);

extern PCD_HandleTypeDef hpcd;

#endif