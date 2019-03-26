#include "main.h"

int main()
{
    HAL_Init();

    SystemClockConfig();

    SetupKeyboard();
    SetupGPIO();

    int flashDelay = 0;
    while (1)
    {
        UpdateKeyboard();

        if (flashDelay >= 10000)
        {
            flashDelay = 0;
            HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
        }

        for (int i = 0; i < keyCount; i++)
        {
            if (!HAL_GPIO_ReadPin(keys[i].Pin.Port, keys[i].Pin.Pin))
            {
                HAL_GPIO_WritePin(statusLeds[i].Port, statusLeds[i].Pin, GPIO_PIN_SET);
            }
            else
            {
                HAL_GPIO_WritePin(statusLeds[i].Port, statusLeds[i].Pin, GPIO_PIN_RESET);
            }
        }

        flashDelay += 1;
    }
}

void SetupGPIO()
{
    static GPIO_InitTypeDef GPIO_InitStruct;

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();

    // Configure the onboard LED
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Pin = GPIO_PIN_3;

    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // Configure the output LEDs
    for (int i = 0; i < statusLedsCount; i++)
    {
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Pin = statusLeds[i].Pin;

        HAL_GPIO_Init(statusLeds[i].Port, &GPIO_InitStruct);
    }
}

void SystemClockConfig(void)
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;
    RCC_CRSInitTypeDef RCC_CRSInitStruct;

    // Enable HSI48 Oscillator to be used as system clock source
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    // Select HSI48 as USB clock source
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USB;
    PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

    // Select HSI48 as the system clock source, and configure HCLK and PCLK1 clock dividers
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI48;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);

    __HAL_RCC_CRS_CLK_ENABLE();

    RCC_CRSInitStruct.Prescaler = RCC_CRS_SYNC_DIV1;
    RCC_CRSInitStruct.Source = RCC_CRS_SYNC_SOURCE_USB;
    RCC_CRSInitStruct.ReloadValue = __HAL_RCC_CRS_RELOADVALUE_CALCULATE(48000000, 1000);
    RCC_CRSInitStruct.ErrorLimitValue = RCC_CRS_ERRORLIMIT_DEFAULT;
    RCC_CRSInitStruct.HSI48CalibrationValue = 0x20;
    HAL_RCCEx_CRSConfig(&RCC_CRSInitStruct);

    __HAL_RCC_PWR_CLK_ENABLE();
}
