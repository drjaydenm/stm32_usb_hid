#include "keyboard.h"

KeyboardKey keys[] =
{
    { KEY_A, { GPIOA, GPIO_PIN_0 }, KEY_STATE_UP },
    { KEY_B, { GPIOA, GPIO_PIN_1 }, KEY_STATE_UP },
    { KEY_C, { GPIOA, GPIO_PIN_3 }, KEY_STATE_UP },
    { KEY_MACRO_0, { GPIOA, GPIO_PIN_4 }, KEY_STATE_UP }
};
const int keyCount = sizeof(keys) / sizeof(keys[0]);

uint8_t anyKeyDown = 0;
uint8_t macroKeyDown = 0;
uint8_t macroStep = 0;
uint32_t macroMillis = 0;

void SetupKeyboard() {
    static GPIO_InitTypeDef GPIO_InitStruct;

    USBD_Init(&USBD_Device, &HID_Desc, 0);
    USBD_RegisterClass(&USBD_Device, &USBD_HID);
    USBD_Start(&USBD_Device);
    
    // Configure the key pins for input
    for (int i = 0; i < keyCount; i++)
    {
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Pin = keys[i].Pin.Pin;

        HAL_GPIO_Init(keys[i].Pin.Port, &GPIO_InitStruct);
    }
}

void UpdateKeyboard() {
    if (!macroKeyDown)
    {
        ScanKeys();
    }

    if (macroKeyDown)
    {
        HandleMacroKey();
    }
    else
    {
        HandleStandardKeys();
    }
}

void ScanKeys()
{
    uint32_t millis = HAL_GetTick();
    macroKeyDown = 0;
    anyKeyDown = 0;

    for (int i = 0; i < keyCount; i++)
    {
        uint8_t pinState = HAL_GPIO_ReadPin(keys[i].Pin.Port, keys[i].Pin.Pin);
        if (pinState != keys[i].State)
        {
            if (millis - keys[i].StateChangeMillis > DEBOUNCE_MILLIS)
            {
                keys[i].State = pinState;
                keys[i].StateChangeMillis = millis;
            }
        }

        if (keys[i].State == KEY_STATE_DOWN)
        {
            anyKeyDown = 1;
        }

        if ((keys[i].Key == KEY_MACRO_0 || keys[i].Key == KEY_MACRO_1) && keys[i].State == KEY_STATE_DOWN)
        {
            macroKeyDown = keys[i].Key;
            macroMillis = HAL_GetTick();
        }
    }
}

void HandleStandardKeys()
{
    uint8_t currentKey = 0;
    HIDKeyboardReport report = {0};

    if (!anyKeyDown)
    {
        SendNullReport();
        return;
    }

    for (int i = 0; i < keyCount; i++)
    {
        if (keys[i].State == KEY_STATE_DOWN)
        {
            report.Keys[currentKey] = keys[i].Key;
            currentKey++;
        }

        if (currentKey >= REPORT_MAX_KEYS)
        {
            break;
        }
    }

    SendReport(&report);
}

void HandleMacroKey()
{
    HIDKeyboardReport report = {0};
    const uint8_t macro[] = {
        KEY_A,
        KEY_1,
        KEY_B,
        KEY_2,
        KEY_C,
        KEY_3,
        KEY_ENTER
    };
    const uint8_t macroCount = sizeof(macro) / sizeof(macro[0]);

    if (macroStep < macroCount && HAL_GetTick() - macroMillis > 30)
    {
        report.Keys[0] = macro[macroStep];
        SendReport(&report);
        macroStep++;
        macroMillis = HAL_GetTick();
    }

    if (macroStep >= macroCount)
    {
        macroStep = 0;
        macroKeyDown = 0;
    }
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

void ResetReport(HIDKeyboardReport* report)
{
    report->Modifiers = 0;
    report->Keys[0] = 0;
    report->Keys[1] = 0;
    report->Keys[2] = 0;
    report->Keys[3] = 0;
    report->Keys[4] = 0;
    report->Keys[5] = 0;
}