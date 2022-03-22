#include "Terminal.h"

#include "Clock.h"

#include "pico/stdlib.h"

#include <cstring>
#include <stdio.h>

Terminal Terminal::terminal;

static char input[16] = { 0 };
static uint8_t count = 0;

void Terminal::Init()
{
    mState = TS_MENU;
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

        switch (mState)
        {
            case TS_MENU:
            {
                if ('1' == ch)
                {
                    mState = TS_TIME_HOUR;
                    printf("\r\nEnter the hour: ");
                }
                else if ('2' == ch)
                {
                    mState = TS_DATE_YEAR;
                    printf("\r\nEnter the year: ");
                }
            }
            break;

            case TS_TIME_HOUR:
            {
                input[count] = ch;
                count++;
                if (count >= 2)
                {
                    mState = TS_TIME_MIN;
                    printf("\r\nEnter the minute: ");
                }
            }
            break;

            case TS_TIME_MIN:
            {
                input[count] = ch;
                count++;
                if (count >= 4)
                {
                    mState = TS_TIME_SEC;
                    printf("\r\nEnter the second: ");
                }
            }
            break;

            case TS_TIME_SEC:
            {
                input[count] = ch;
                count++;
                if (count >= 6)
                {
                    mState = TS_MENU;

                    uint8_t lHour = 10 * ((uint8_t)input[0] - 0x30) + ((uint8_t)input[1] - 0x30);
                    uint8_t lMin = 10 * ((uint8_t)input[2] - 0x30) + ((uint8_t)input[3] - 0x30);
                    uint8_t lSec = 10 * ((uint8_t)input[4] - 0x30) + ((uint8_t)input[5] - 0x30);

                    Clock::clock.SetTime(lHour, lMin, lSec);

                    memset(input, 0, sizeof(input));
                    count = 0;
                    PrintMenu();
                }
            }
            break;

            case TS_DATE_YEAR:
            {
                input[count] = ch;
                count++;
                if (count >= 4)
                {
                    mState = TS_DATE_MONTH;
                    printf("\r\nEnter the month: ");
                }
            }
            break;

            case TS_DATE_MONTH:
            {
                input[count] = ch;
                count++;
                if (count >= 6)
                {
                    mState = TS_DATE_DAY;
                    printf("\r\nEnter the day: ");
                }
            }
            break;

            case TS_DATE_DAY:
            {
                input[count] = ch;
                count++;
                if (count >= 8)
                {
                    mState = TS_DATE_DAY_OF_WEEK;
                    printf("\r\nEnter the day of the week (Sunday == 0): ");
                }
            }
            break;

            case TS_DATE_DAY_OF_WEEK:
            {
                input[count] = ch;
                count++;
                if (count >= 9)
                {
                    mState = TS_MENU;

                    uint16_t lYear = 1000 * ((uint16_t)input[0] - 0x30) + 100 * ((uint16_t)input[1] - 0x30) + 10 * ((uint16_t)input[2] - 0x30) + ((uint16_t)input[3] - 0x30);
                    uint8_t lMonth = 10 * ((uint8_t)input[4] - 0x30) + ((uint8_t)input[5] - 0x30);
                    uint8_t lDay = 10 * ((uint8_t)input[6] - 0x30) + ((uint8_t)input[7] - 0x30);
                    uint8_t lDayOfWeek = ((uint8_t)input[8] - 0x30);

                    Clock::clock.SetDate(lYear, lMonth, lDay, lDayOfWeek);

                    memset(input, 0, sizeof(input));
                    count = 0;
                    PrintMenu();
                }
            }
            break;

            default:
            {
            }
            break;
        }

        ch = getchar_timeout_us(0);
    }
}

void Terminal::PrintWelcome()
{
    printf("\n\nWelcome to pico-clock terminal!");
}

void Terminal::PrintMenu()
{
    printf("\n\n-------- MENU --------\n");
    printf("1 - Set Time\n");
    printf("2 - Set Date\n\n");
}
