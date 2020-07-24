#include "Emulator.h"

Emulator::Emulator(sf::RenderWindow& window)
    : window(window)
{
}

int Emulator::ExecuteNextOpcode()
{
    return 1;
}

void Emulator::UpdateTimers(int cycles)
{
}

void Emulator::UpdateGraphics(int cycles)
{
}

void Emulator::DoInterupts()
{
}

void Emulator::Update()
{
    const int MAXCYCLES = 69905;
    int cyclesThisUpdate = 0;

    while (cyclesThisUpdate < MAXCYCLES)
    {
        int cycles = ExecuteNextOpcode();
        cyclesThisUpdate += cycles;
        UpdateTimers(cycles);
        UpdateGraphics(cycles);
        DoInterupts();
    }
    RenderScreen();
}

void Emulator::RenderScreen()
{
}
