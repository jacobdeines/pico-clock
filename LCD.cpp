#include "LCD.h"

#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "pico/stdlib.h"

LCD LCD::lcd;

const char *LCD::RESET = "|-";

void LCD::Init()
{
    sleep_ms(1);

    Reset();

    sleep_ms(1);

    PrintString("Starting up...", false);

    sleep_ms(1);

    Reset();

    sleep_ms(1);
}

void LCD::Reset()
{
    PrintStringLen(RESET, 2, true);
}

void LCD::WriteByte(uint8_t val)
{
    i2c_write_blocking(i2c_default, DEFAULT_LCD_ADDR, &val, 1, false);
    sleep_us(200);
}

void LCD::PrintString(const char *s, bool reset)
{
    while (*s)
    {
        WriteByte(*s++);
    }
    sleep_us(500);
    if (true == reset)
    {
        WriteByte(0xFE);
        WriteByte(128 + ROW_0_START + 0);
        sleep_us(500);
    }
}

void LCD::PrintStringLen(const char *s, uint8_t len, bool reset)
{
    i2c_write_blocking(i2c_default, DEFAULT_LCD_ADDR, (uint8_t *)s, len, false);
    sleep_us(500);
    if (true == reset)
    {
        WriteByte(0xFE);
        WriteByte(128 + ROW_0_START + 0);
        sleep_us(500);
    }
}

void LCD::SetColor(uint8_t r, uint8_t g, uint8_t b)
{
    WriteByte('|');
    WriteByte('+');
    WriteByte(r);
    WriteByte(g);
    WriteByte(b);
}

void LCD::PrintStringAtLocation(uint8_t row, uint8_t col, char *s)
{
    if ((row < LCD_ROWS) &&
        (col < LCD_COLS))
    {
        switch (row)
        {
            case 0:
            {
                WriteByte(0xFE);
                WriteByte(128 + ROW_0_START + col);
                sleep_us(100);
                PrintString(s, false);
            }
            break;

            case 1:
            {
                WriteByte(0xFE);
                WriteByte(128 + ROW_1_START + col);
                sleep_us(100);
                PrintString(s, false);
            }
            break;

            case 2:
            {
                WriteByte(0xFE);
                WriteByte(128 + ROW_2_START + col);
                sleep_us(100);
                PrintString(s, false);
            }
            break;

            case 3:
            {
                WriteByte(0xFE);
                WriteByte(128 + ROW_3_START + col);
                sleep_us(100);
                PrintString(s, false);
            }
            break;

            default:
            {
            }
            break;
        }
    }
}

void LCD::PrintCharAtLocation(uint8_t row, uint8_t col, char s)
{
    if ((row < LCD_ROWS) &&
        (col < LCD_COLS))
    {
        switch (row)
        {
            case 0:
            {
                WriteByte(0xFE);
                WriteByte(128 + ROW_0_START + col);
                sleep_us(100);
                WriteByte(s);
            }
            break;

            case 1:
            {
                WriteByte(0xFE);
                WriteByte(128 + ROW_1_START + col);
                sleep_us(100);
                WriteByte(s);
            }
            break;

            case 2:
            {
                WriteByte(0xFE);
                WriteByte(128 + ROW_2_START + col);
                sleep_us(100);
                WriteByte(s);
            }
            break;

            case 3:
            {
                WriteByte(0xFE);
                WriteByte(128 + ROW_3_START + col);
                sleep_us(100);
                WriteByte(s);
            }
            break;

            default:
            {
            }
            break;
        }
    }
}

void LCD::SetCursorLocation(uint8_t row, uint8_t col)
{
    if ((row < LCD_ROWS) &&
        (col < LCD_COLS))
    {
        switch (row)
        {
            case 0:
            {
                WriteByte(0xFE);
                WriteByte(128 + ROW_0_START + col);
            }
            break;

            case 1:
            {
                WriteByte(0xFE);
                WriteByte(128 + ROW_1_START + col);
            }
            break;

            case 2:
            {
                WriteByte(0xFE);
                WriteByte(128 + ROW_2_START + col);
            }
            break;

            case 3:
            {
                WriteByte(0xFE);
                WriteByte(128 + ROW_3_START + col);
                
            }
            break;

            default:
            {
            }
            break;
        }
    }
    sleep_us(500);
}
