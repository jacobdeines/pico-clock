#ifndef SYSTEM_TIMING_H
#define SYSTEM_TIMING_H

#include <cstdint>

class SystemTiming
{
public:
	static uint32_t TimerTimestamp_ms();
	static uint64_t TimerTimestamp_us();
    static uint32_t TimeElapsed_ms(uint32_t aTimestamp);
	static uint64_t TimeElapsed_us(uint64_t aTimestamp);
	static bool TimeExpired_ms(uint32_t aTimestamp, uint32_t aTimeLimit);
	static bool TimeExpired_us(uint64_t aTimestamp, uint64_t aTimeLimit);

private:
	SystemTiming();
	~SystemTiming();
};

#endif // SYSTEM_TIMING_H
