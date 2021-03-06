#include "Clock.h"

#include "DS3231.h"
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

    sleep_ms(500);

    DS3231::ds3231.ReadDateTime();

    sleep_ms(5);

    datetime_struct.year = DS3231::ds3231.GetYear();
    datetime_struct.month = DS3231::ds3231.GetMonth();
    datetime_struct.day = DS3231::ds3231.GetDay();
    datetime_struct.dotw = DS3231::ds3231.GetDayOfWeek() - 1;
    datetime_struct.hour = DS3231::ds3231.GetHour();
    datetime_struct.min = DS3231::ds3231.GetMinute();
    datetime_struct.sec = DS3231::ds3231.GetSecond();

    // Start the on-board RTC and set date/time
    rtc_init();
    rtc_set_datetime(&datetime_struct);

    Update();
}

void Clock::Update()
{
    char buf[64] = "";

    rtc_get_datetime(&datetime_struct);

    if (datetime_struct.year != mYear)
    {
        mYear = datetime_struct.year;
    }

    if (datetime_struct.month != mMonth)
    {
        mMonth = datetime_struct.month;
    }

    if (datetime_struct.day != mDay)
    {
        mDay = datetime_struct.day;
    }

    if (datetime_struct.dotw != mDayOfWeek)
    {
        mDayOfWeek = datetime_struct.dotw;
    }

    if (datetime_struct.hour != mHour)
    {
        mHour = datetime_struct.hour;
    }

    if (datetime_struct.min != mMinute)
    {
        mMinute = datetime_struct.min;
    }

    if (datetime_struct.sec != mSecond)
    {
        mSecond = datetime_struct.sec;

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

        if (true == pm)
        {
            sprintf(buf, "%02u:%02u:%02u PM     ", lHour, mMinute, mSecond);
        }
        else
        {
            sprintf(buf, "%02u:%02u:%02u AM     ", lHour, mMinute, mSecond);
        }
        LCD::lcd.PrintStringLen(buf, 16, false);

        switch (mDayOfWeek)
        {
            case 0:
            {
                sprintf(buf, "%02u/%02u/%04u - SUN", mMonth, mDay, mYear);
            }
            break;

            case 1:
            {
                sprintf(buf, "%02u/%02u/%04u - MON", mMonth, mDay, mYear);
            }
            break;

            case 2:
            {
                sprintf(buf, "%02u/%02u/%04u - TUE", mMonth, mDay, mYear);
            }
            break;

            case 3:
            {
                sprintf(buf, "%02u/%02u/%04u - WED", mMonth, mDay, mYear);
            }
            break;

            case 4:
            {
                sprintf(buf, "%02u/%02u/%04u - THU", mMonth, mDay, mYear);
            }
            break;

            case 5:
            {
                sprintf(buf, "%02u/%02u/%04u - FRI", mMonth, mDay, mYear);
            }
            break;

            case 6:
            {
                sprintf(buf, "%02u/%02u/%04u - SAT", mMonth, mDay, mYear);
            }
            break;

            default:
            {
                sprintf(buf, "%02u/%02u/%04u - ERR", mMonth, mDay, mYear);
            }
            break;
        }
        LCD::lcd.PrintStringLen(buf, 16, true);
    }
}

void Clock::SetDate(uint16_t aYear, uint8_t aMonth, uint8_t aDay, uint8_t aDayOfWeek)
{
    datetime_struct.year = aYear;
    datetime_struct.month = aMonth;
    datetime_struct.day = aDay;
    datetime_struct.dotw = aDayOfWeek;

    DS3231::ds3231.SetDate(aYear, aMonth, aDay, aDayOfWeek + 1);

    rtc_set_datetime(&datetime_struct);
}

void Clock::SetTime(uint8_t aHour, uint8_t aMinute, uint8_t aSecond)
{
    datetime_struct.hour = aHour;
    datetime_struct.min = aMinute;
    datetime_struct.sec = aSecond;

    DS3231::ds3231.SetTime(aHour, aMinute, aSecond);

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
