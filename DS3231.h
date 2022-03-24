#ifndef DS3231_H
#define DS3231_H

#include "pico/stdlib.h"

#include <cstring>
#include <stdio.h>

#define DEFAULT_DS3231_ADDR 0x68

class DS3231
{
public:
    static DS3231 ds3231;

    DS3231();
    ~DS3231();

    void ReadDateTime();

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
    uint8_t mDataBuffer[18];
};

#endif // DS3231_H
