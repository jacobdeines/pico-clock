#ifndef TERMINAL_H
#define TERMINAL_H

class Terminal
{
public:
    static Terminal terminal;

    void Init();
    void Update();
    void PrintWelcome();
    void PrintMenu();
};

#endif // TERMINAL_H
