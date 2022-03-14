#include "LCD.h"

#include "hardware/i2c.h"

const char *LCD::RESET = "|-";

void LCD::WriteByte(uint8_t val)
{
    i2c_write_blocking(i2c_default, DEFAULT_LCD_ADDR, &val, 1, false);
}

void LCD::PrintString(const char *s)
{
    while (*s)
    {
        WriteByte(*s++);
        sleep_us(50);
    }
}

void LCD::Reset()
{
    PrintString(RESET);
}