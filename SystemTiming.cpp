#include "SystemTiming.h"

#include "pico/stdlib.h"

#include <limits.h>
#include <climits>

uint32_t SystemTiming::TimerTimestamp_ms()
{
    return to_ms_since_boot(get_absolute_time());
}

uint64_t SystemTiming::TimerTimestamp_us()
{
    return to_us_since_boot(get_absolute_time());
}

uint32_t SystemTiming::TimeElapsed_ms(uint32_t aTimestamp)
{
    uint32_t retVal;
	uint32_t lTimestamp = TimerTimestamp_ms();

	if (lTimestamp >= aTimestamp)
	{
		retVal = lTimestamp - aTimestamp;
	}
	else
	{
		retVal = (ULONG_MAX - aTimestamp) + lTimestamp + 1;
	}
	return retVal;
}

uint64_t SystemTiming::TimeElapsed_us(uint64_t aTimestamp)
{
    uint64_t retVal;
	uint64_t lTimestamp = TimerTimestamp_us();

	if (lTimestamp >= aTimestamp)
	{
		retVal = lTimestamp - aTimestamp;
	}
	else
	{
		retVal = (ULLONG_MAX - aTimestamp) + lTimestamp + 1;
	}
	return retVal;
}

bool SystemTiming::TimeExpired_ms(uint32_t aTimestamp, uint32_t aTimeLimit)
{
    bool retVal;
	uint32_t lTimestamp = TimerTimestamp_ms();

	if (lTimestamp >= aTimestamp)
	{
		retVal = ((lTimestamp - aTimestamp) >= aTimeLimit);
	}
	else
	{
		retVal = (((ULONG_MAX - aTimestamp) + lTimestamp + 1) >= aTimeLimit);
	}
	return retVal;
}

bool SystemTiming::TimeExpired_us(uint64_t aTimestamp, uint64_t aTimeLimit)
{
    bool retVal;
	uint64_t lTimestamp = TimerTimestamp_us();

	if (lTimestamp >= aTimestamp)
	{
		retVal = ((lTimestamp - aTimestamp) >= aTimeLimit);
	}
	else
	{
		retVal = (((ULLONG_MAX - aTimestamp) + lTimestamp + 1) >= aTimeLimit);
	}
	return retVal;
}

SystemTiming::SystemTiming()
{
}

SystemTiming::~SystemTiming()
{
}