#include "Terminal.h"

#include <stdio.h>

void Terminal::PrintWelcome()
{
    printf("\n\nWelcome to pico-clock terminal!\n\n");
}

void Terminal::PrintMenu()
{
    printf("-------- MENU --------\n");
    printf("1 - Set Time and Date\n");
    printf("2 - Set Message\n");
    printf("3 - Set Color\n");
}