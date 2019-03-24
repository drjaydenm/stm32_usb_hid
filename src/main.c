#include "main.h"

int main ()
{
    HAL_Init();

    SystemClockConfig();

    SetupGPIO();

    int flashDelay = 0;
    while (1)
    {
        if (flashDelay >= 100000)
        {
            flashDelay = 0;
            HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
        }

        for (int i = 0; i < scanRowsCount; i++)
        {
            if (!HAL_GPIO_ReadPin(scanRows[i].Port, scanRows[i].Pin))
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

    // Configure the input keys
    for (int i = 0; i < scanRowsCount; i++)
    {
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Pin = scanRows[i].Pin;

        HAL_GPIO_Init(scanRows[i].Port, &GPIO_InitStruct);
    }
}

void SystemClockConfig(void)
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;

    // No HSE Oscillator on Nucleo, Activate PLL with HSI as source
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_NONE;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
    {
        // Initialization Error
        while(1);
    }

    // Select PLL as system clock source and configure the HCLK, PCLK1 clocks dividers
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
    {
        // Initialization Error
        while(1);
    }
}