#include "Clock.h"

#include "LCD.h"

#include "hardware/i2c.h"
#include "hardware/rtc.h"
#include "pico/binary_info.h"
#include "pico/stdlib.h"

#include <string.h>
#include <stdio.h>

Clock Clock::clock;

void Clock::Init()
{
    mYear = 0xFFFF;
    mMonth = 0xFF;
    mDay = 0xFF;
    mDayOfWeek = 0xFF;
    mHour = 0xFF;
    mMinute = 0xFF;
    mSecond = 0xFF;

    // Default date/time
    datetime_struct = {
            .year  = 2020,
            .month = 1,
            .day   = 1,
            .dotw  = 3,
            .hour  = 0,
            .min   = 0,
            .sec   = 0
    };

    // Get initial date/time from external RTC
    // TODO: jdd

    // Start the on-board RTC and set date/time
    rtc_init();
    rtc_set_datetime(&datetime_struct);

    char buf[2] = ":";
    LCD::lcd.PrintStringAtLocation(0, 2, buf);
    LCD::lcd.PrintStringAtLocation(0, 5, buf);
    buf[0] = '/';
    LCD::lcd.PrintStringAtLocation(1, 2, buf);
    LCD::lcd.PrintStringAtLocation(1, 5, buf);
    buf[0] = '-';
    LCD::lcd.PrintStringAtLocation(1, 11, buf);

    Update();
}

void Clock::Update()
{
    char buf[5] = "";

    rtc_get_datetime(&datetime_struct);

    if (datetime_struct.year != mYear)
    {
        mYear = datetime_struct.year;
        sprintf(buf, "%04u", mYear);
        LCD::lcd.PrintStringAtLocation(1, 6, buf);
    }

    if (datetime_struct.month != mMonth)
    {
        mMonth = datetime_struct.month;
        sprintf(buf, "%02u", mMonth);
        LCD::lcd.PrintStringAtLocation(1, 0, buf);
    }

    if (datetime_struct.day != mDay)
    {
        mDay = datetime_struct.day;
        sprintf(buf, "%02u", mDay);
        LCD::lcd.PrintStringAtLocation(1, 3, buf);
    }

    if (datetime_struct.dotw != mDayOfWeek)
    {
        mDayOfWeek = datetime_struct.dotw;
        switch (mDayOfWeek)
        {
            case 0:
            {
                sprintf(buf, "SUN");
            }
            break;

            case 1:
            {
                sprintf(buf, "MON");
            }
            break;

            case 2:
            {
                sprintf(buf, "TUE");
            }
            break;

            case 3:
            {
                sprintf(buf, "WED");
            }
            break;

            case 4:
            {
                sprintf(buf, "THU");
            }
            break;

            case 5:
            {
                sprintf(buf, "FRI");
            }
            break;

            case 6:
            {
                sprintf(buf, "SAT");
            }
            break;

            default:
            {
                sprintf(buf, "ERR");
            }
            break;
        }
        LCD::lcd.PrintStringAtLocation(1, 13, buf);
    }

    if (datetime_struct.hour != mHour)
    {
        mHour = datetime_struct.hour;

        uint8_t lHour = 0;
        bool pm = false;

        if (0 == mHour)
        {
            lHour = 12;
        }
        else if (mHour < 12)
        {
            lHour = mHour;
        }
        else if (12 == mHour)
        {
            lHour = 12;
            pm = true;
        }
        else
        {
            lHour = mHour - 12;
            pm = true;
        }
        sprintf(buf, "%02u", lHour);
        LCD::lcd.PrintStringAtLocation(0, 0, buf);

        if (true == pm)
        {
            sprintf(buf, "PM");
        }
        else
        {
            sprintf(buf, "AM");
        }
        
        LCD::lcd.PrintStringAtLocation(0, 9, buf);
    }

    if (datetime_struct.min != mMinute)
    {
        mMinute = datetime_struct.min;
        sprintf(buf, "%02u", mMinute);
        LCD::lcd.PrintStringAtLocation(0, 3, buf);
    }

    if (datetime_struct.sec != mSecond)
    {
        mSecond = datetime_struct.sec;
        sprintf(buf, "%02u", mSecond);
        LCD::lcd.PrintStringAtLocation(0, 6, buf);
    }
}

void Clock::SetDate(uint16_t aYear, uint8_t aMonth, uint8_t aDay, uint8_t aDayOfWeek)
{
    datetime_struct.year = aYear;
    datetime_struct.month = aMonth;
    datetime_struct.day = aDay;
    datetime_struct.dotw = aDayOfWeek;

    // TODO: jdd - Set new date on external RTC

    rtc_set_datetime(&datetime_struct);
}

void Clock::SetTime(uint8_t aHour, uint8_t aMinute, uint8_t aSecond)
{
    datetime_struct.hour = aHour;
    datetime_struct.min = aMinute;
    datetime_struct.sec = aSecond;

    // TODO: jdd - Set new time on external RTC

    rtc_set_datetime(&datetime_struct);
}

uint16_t Clock::GetYear()
{
    return mYear;
}

uint8_t Clock::GetMonth()
{
    return mMonth;
}

uint8_t Clock::GetDay()
{
    return mDay;
}

uint8_t Clock::GetDayOfWeek()
{
    return mDayOfWeek;
}

uint8_t Clock::GetHour()
{
    return mHour;
}

uint8_t Clock::GetMinute()
{
    return mMinute;
}

uint8_t Clock::GetSecond()
{
    return mSecond;
}
