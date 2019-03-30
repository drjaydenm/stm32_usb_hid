#include "macros.h"

uint8_t GenerateGuid(char* buffer)
{
    srand(HAL_GetTick());
    static const char *guidTemplate = "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx";
    static const char *guidCharacters = "0123456789ABCDEF-";
    uint8_t guidLength = strlen(guidTemplate);

    for (uint8_t i = 0; i <= guidLength; i++)
    {
        uint8_t r = rand() % 16;
        char c = ' ';

        switch (guidTemplate[i])
        {
            case 'x': { c = guidCharacters[r]; } break;
            case 'y': { c = guidCharacters[r & (0x03 | 0x08)]; } break;
            case '-': { c = '-'; } break;
            case '4': { c = '4'; } break;
        }

        buffer[i] = (i < guidLength) ? c : 0x00;
    }

    return guidLength;
}