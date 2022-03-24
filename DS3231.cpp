#include "ds3231.h"

#include "hardware/i2c.h"

#include <cstring>
#include <stdio.h>

DS3231 DS3231::ds3231;

uint8_t decToBcd(uint8_t val);
uint8_t bcdToDec(uint8_t val);

DS3231::DS3231()
{
    memset(mDataBuffer, 0, sizeof(mDataBuffer));
}

void DS3231::ReadDateTime()
{
    uint8_t lAddr = 0x00;
	i2c_write_blocking(i2c_default, DEFAULT_DS3231_ADDR, &lAddr, 1, true);
	i2c_read_blocking(i2c_default, DEFAULT_DS3231_ADDR, mDataBuffer, 7, false);
    printf("Time values: %04u %02u %02u %u %02u %02u %02u\r\n\r\n", DS3231::ds3231.GetYear(), DS3231::ds3231.GetMonth(), DS3231::ds3231.GetDay(), DS3231::ds3231.GetDayOfWeek(), DS3231::ds3231.GetHour(), DS3231::ds3231.GetMinute(), DS3231::ds3231.GetSecond());
}

void DS3231::SetDate(uint16_t aYear, uint8_t aMonth, uint8_t aDay, uint8_t aDayOfWeek)
{
    uint8_t lBuf[2] = {0x00, 0x00};

    // Set day of week
    if ((aDayOfWeek > 0) &&
        (aDayOfWeek < 8))
    {
        lBuf[0] = 0x03;
        lBuf[1] = decToBcd(aDayOfWeek);
        i2c_write_blocking(i2c_default, DEFAULT_DS3231_ADDR, lBuf, 2, false);
    }

    // Set day
    if ((aDay > 0) &&
        (aDay < 32))
    {
        lBuf[0] = 0x04;
        lBuf[1] = decToBcd(aDay);
        i2c_write_blocking(i2c_default, DEFAULT_DS3231_ADDR, lBuf, 2, false);
    }

    // Set month
    if ((aMonth > 0) &&
        (aMonth < 13))
    {
        lBuf[0] = 0x05;
        lBuf[1] = decToBcd(aMonth);
        i2c_write_blocking(i2c_default, DEFAULT_DS3231_ADDR, lBuf, 2, false);
    }

    // Set year
    uint16_t lYear = aYear % 100;
    lBuf[0] = 0x06;
    lBuf[1] = decToBcd(lYear);
    i2c_write_blocking(i2c_default, DEFAULT_DS3231_ADDR, lBuf, 2, false);
}

void DS3231::SetTime(uint8_t aHour, uint8_t aMinute, uint8_t aSecond)
{
    uint8_t lBuf[2] = {0x00, 0x00};

	// Set seconds
    if (aSecond < 60)
    {
        lBuf[0] = 0x00;
        lBuf[1] = decToBcd(aSecond);
        i2c_write_blocking(i2c_default, DEFAULT_DS3231_ADDR, lBuf, 2, false);
    }

    // Set minutes
    if (aMinute < 60)
    {
        lBuf[0] = 0x01;
        lBuf[1] = decToBcd(aMinute);
        i2c_write_blocking(i2c_default, DEFAULT_DS3231_ADDR, lBuf, 2, false);
    }

    // Set hours
    if (aHour < 24)
    {
        lBuf[0] = 0x02;
        lBuf[1] = decToBcd(aHour) & 0xBF;
        i2c_write_blocking(i2c_default, DEFAULT_DS3231_ADDR, lBuf, 2, false);        
    }
}

uint16_t DS3231::GetYear()
{
    return bcdToDec(mDataBuffer[6]) + 2000;
}

uint8_t DS3231::GetMonth()
{
    return bcdToDec(mDataBuffer[5] & 0x7F);
}

uint8_t DS3231::GetDay()
{
    return bcdToDec(mDataBuffer[4]);
}

uint8_t DS3231::GetDayOfWeek()
{
    return bcdToDec(mDataBuffer[3]);
}

uint8_t DS3231::GetHour()
{
    return bcdToDec(mDataBuffer[2] & 0x3F);
}

uint8_t DS3231::GetMinute()
{
    return bcdToDec(mDataBuffer[1]);
}

uint8_t DS3231::GetSecond()
{
    return bcdToDec(mDataBuffer[0]);
}

uint8_t decToBcd(uint8_t val)
{
    // Convert normal decimal numbers to binary coded decimal
    return ( (val/10*16) + (val%10) );
}
 
uint8_t bcdToDec(uint8_t val)
{
    // Convert binary coded decimal to normal decimal numbers
    return ( (val/16*10) + (val%16) );
}
