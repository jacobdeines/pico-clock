#include "Clock.h"
#include "LCD.h"
#include "SystemTiming.h"
#include "Terminal.h"

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define UPDATE_LOOP_TIMEOUT_MS 1
#define LED_BLINK_TIMEOUT_MS 500

static uint32_t updateTimestamp_ms = 0;
static uint32_t ledBlinkTimeout_ms = 0;

int main()
{
    stdio_init_all();

    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    LCD::lcd.Init();
    LCD::lcd.SetColor(0, 255, 255);

    Terminal::terminal.Init();
    Terminal::terminal.PrintWelcome();
    Terminal::terminal.PrintMenu();

    Clock::clock.Init();

    bool ledState = false;
    gpio_put(25, 0);

    while (true)
    {
        Terminal::terminal.Update();

        if (true == SystemTiming::TimeExpired_ms(updateTimestamp_ms, UPDATE_LOOP_TIMEOUT_MS))
        {
            Clock::clock.Update();

            if (true == SystemTiming::TimeExpired_ms(ledBlinkTimeout_ms, LED_BLINK_TIMEOUT_MS))
            {
                gpio_put(25, (ledState ? 1 : 0));
                ledState = !ledState;
                ledBlinkTimeout_ms = SystemTiming::TimerTimestamp_ms();
            }

            updateTimestamp_ms = SystemTiming::TimerTimestamp_ms();
        }
    }

    return 0;
}
