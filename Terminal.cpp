#include "Terminal.h"

#include "pico/stdlib.h"

#include <stdio.h>

Terminal Terminal::terminal;

void Terminal::Init()
{
    printf("\n\n");
}

void Terminal::Update()
{
    int16_t ch = getchar_timeout_us(0);

    while (PICO_ERROR_TIMEOUT != ch)
    {
        if (255 != ch)
        {
            if ('\r' == ch)
            {
                printf("%c", '\n');
            }
            else
            {
                printf("%c", ch);
            }
        }
        ch = getchar_timeout_us(0);
    }
}

void Terminal::PrintWelcome()
{
    printf("Welcome to pico-clock terminal!\n\n");
}

void Terminal::PrintMenu()
{
    printf("-------- MENU --------\n");
    printf("1 - Set Time\n");
    printf("2 - Set Date\n");
    printf("3 - Set Message\n");
    printf("4 - Set Color\n");
}
