#ifndef LCD_H
#define LCD_H

#include <stdint.h>

#define DEFAULT_LCD_ADDR 0x72
#define DEFAULT_LCD_ROWS 4
#define DEFAULT_LCD_COLS 20

class LCD
{
public:
    void WriteByte(uint8_t val);

    void PrintString(const char *s);

    void Reset();

private:
    static const char *RESET;
};

#endif // LCD_H