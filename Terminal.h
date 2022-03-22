#ifndef TERMINAL_H
#define TERMINAL_H

class Terminal
{
public:
    enum TERMINAL_STATE_ENUM
    {
        TS_MENU = 0,
        TS_TIME_HOUR = 1,
        TS_TIME_MIN = 2,
        TS_TIME_SEC = 3,
        TS_DATE_YEAR = 4,
        TS_DATE_MONTH = 5,
        TS_DATE_DAY = 6,
        TS_DATE_DAY_OF_WEEK = 7
    };

    static Terminal terminal;

    void Init();
    void Update();
    void PrintWelcome();
    void PrintMenu();

private:
    TERMINAL_STATE_ENUM mState;
};

#endif // TERMINAL_H
