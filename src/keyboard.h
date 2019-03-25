#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include "usbd_desc.h"
#include "usbd_hid.h"
#include "gpio_pin.h"

#define REPORT_BUF_SIZE 8

typedef struct
{
    uint8_t Modifiers;
    uint8_t Keys[6];
}
HIDKeyboardReport; 

__ALIGN_BEGIN uint8_t _reportBuffer[REPORT_BUF_SIZE] __ALIGN_END;
USBD_HandleTypeDef USBD_Device;

void SetupKeyboard();
void UpdateKeyboard();
void SendNullReport();
void SendReport(const HIDKeyboardReport* report);
void CopyReportToBuffer(const HIDKeyboardReport* report, uint8_t* buffer);

#endif