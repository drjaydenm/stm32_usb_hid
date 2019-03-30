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
uint8_t macroCount = 0;
uint8_t macroNextKeySame = 0;
uint32_t macroMillis = 0;
char macroContent[100] = {0};

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
    // Only scan for key states if we aren'y processing a macro
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

        if ((keys[i].Key == KEY_MACRO_0 || keys[i].Key == KEY_MACRO_1)
            && keys[i].State == KEY_STATE_DOWN)
        {
            BeginMacroKey(keys[i]);
        }
    }
}

void BeginMacroKey(KeyboardKey key)
{
    macroKeyDown = key.Key;
    macroMillis = HAL_GetTick();

    // Generate the output for the macrow
    if (key.Key == KEY_MACRO_0)
    {
        macroCount = GenerateGuid(macroContent);
    }
}

void EndMacroKey()
{
    macroKeyDown = 0;
    macroStep = 0;
    macroCount = 0;
    macroNextKeySame = 0;

    // Zero out the macro content
    memset(macroContent, 0, 100);
}

void HandleStandardKeys()
{
    uint8_t currentReportKey = 0;
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
            report.Keys[currentReportKey] = keys[i].Key;
            currentReportKey++;
        }

        // We can only send up to REPORT_MAX_KEYS keys at once
        if (currentReportKey >= REPORT_MAX_KEYS)
        {
            break;
        }
    }

    SendReport(&report);
}

void HandleMacroKey()
{
    HIDKeyboardReport report = {0};
    uint32_t currentTick = HAL_GetTick();

    if (macroNextKeySame && currentTick - macroMillis > MACRO_KEY_DELAY)
    {
        SendNullReport();
        macroNextKeySame = 0;
        macroMillis = HAL_GetTick();
        return;
    }

    if (!macroNextKeySame && macroStep < macroCount && currentTick - macroMillis > MACRO_KEY_DELAY)
    {
        report.Keys[0] = CharToKeyCode(macroContent[macroStep]);
        SendReport(&report);

        macroStep++;
        macroMillis = HAL_GetTick();

        // If the next and prev characters are the same, send a null report
        if (macroStep < macroCount && macroContent[macroStep] == macroContent[macroStep - 1])
        {
            macroNextKeySame = 1;
        }

        return;
    }

    if (macroStep >= macroCount)
    {
        SendNullReport();
        EndMacroKey();
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