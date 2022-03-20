#include "LCD.h"

#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "pico/stdlib.h"

LCD LCD::lcd;

const char *LCD::RESET = "|-";

void LCD::Init()
{
    i2c_init(i2c_default, 115200);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
    bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));

    sleep_ms(1);

    Reset();

    sleep_ms(1);

    PrintString("Starting up...");

    sleep_ms(1);

    Reset();

    sleep_ms(1);
}

void LCD::Reset()
{
    PrintString(RESET);
}

void LCD::WriteByte(uint8_t val)
{
    i2c_write_blocking(i2c_default, DEFAULT_LCD_ADDR, &val, 1, false);
    sleep_us(50);
}

void LCD::PrintString(const char *s)
{
    while (*s)
    {
        WriteByte(*s++);
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
                PrintString(s);
            }
            break;

            case 1:
            {
                WriteByte(0xFE);
                WriteByte(128 + ROW_1_START + col);
                PrintString(s);
            }
            break;

            case 2:
            {
                WriteByte(0xFE);
                WriteByte(128 + ROW_2_START + col);
                PrintString(s);
            }
            break;

            case 3:
            {
                WriteByte(0xFE);
                WriteByte(128 + ROW_3_START + col);
                PrintString(s);
            }
            break;

            default:
            {
            }
            break;
        }
    }
}
