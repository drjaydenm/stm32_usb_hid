#include "keyboard.h"

GPIOPin scanRows[] =
{
    { GPIOA, GPIO_PIN_0 },
    { GPIOA, GPIO_PIN_1 },
    { GPIOA, GPIO_PIN_3 },
    { GPIOA, GPIO_PIN_4 },
};
int scanRowsCount = sizeof(scanRows) / sizeof(scanRows[0]);

void SetupKeyboard() {
    USBD_Init(&USBD_Device, &HID_Desc, 0);
    USBD_RegisterClass(&USBD_Device, &USBD_HID);
    USBD_Start(&USBD_Device);
}

void UpdateKeyboard() {
    uint8_t currentKey = 0;
    HIDKeyboardReport report = {0};

    for (int i = 0; i < scanRowsCount; i++)
    {
        if (!HAL_GPIO_ReadPin(scanRows[i].Port, scanRows[i].Pin))
        {
            report.Keys[currentKey] = 0x20 + (0x01 * i);
            currentKey++;
        }

        if (currentKey >= 6) {
            break;
        }
    }

    SendReport(&report);
}

void SendNullReport() {
    HIDKeyboardReport report = {0};
    SendReport(&report);
}

void SendReport(const HIDKeyboardReport* report) {
    if (report == NULL) {
        return;
    }

    CopyReportToBuffer(report, _reportBuffer);

    USBD_HID_SendReport(&USBD_Device, _reportBuffer, REPORT_BUF_SIZE);
}

void CopyReportToBuffer(const HIDKeyboardReport* report, uint8_t* buffer)
{
    buffer[0] = report->Modifiers;
    buffer[1] = 0;
    buffer[2] = report->Keys[0];
    buffer[3] = report->Keys[1];
    buffer[4] = report->Keys[2];
    buffer[5] = report->Keys[3];
    buffer[6] = report->Keys[4];
    buffer[7] = report->Keys[5];
}