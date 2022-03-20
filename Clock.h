#ifndef CLOCK_H
#define CLOCK_H

#include "pico/util/datetime.h"

class Clock
{
public:
    static Clock clock;

    void Init();
    void Update();

    void SetDate(uint16_t aYear, uint8_t aMonth, uint8_t aDay, uint8_t aDayOfWeek);

    void SetTime(uint8_t aHour, uint8_t aMinute, uint8_t aSecond);

    uint16_t GetYear();
    uint8_t GetMonth();
    uint8_t GetDay();
    uint8_t GetDayOfWeek();
    uint8_t GetHour();
    uint8_t GetMinute();
    uint8_t GetSecond();

private:

    datetime_t datetime_struct;

    uint16_t mYear;
    uint8_t mMonth;
    uint8_t mDay;
    uint8_t mDayOfWeek;
    uint8_t mHour;
    uint8_t mMinute;
    uint8_t mSecond;
};

#endif // CLOCK_H
