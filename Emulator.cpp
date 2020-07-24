#include "Emulator.h"

void Emulator::InitState()
{
    //Set initial register values
    m_ProgramCounter = 0x100;
    m_RegisterAF.reg = 0x01B0;
    m_RegisterBC.reg = 0x0013;
    m_RegisterDE.reg = 0x00D8;
    m_RegisterHL.reg = 0x014D;
    m_StackPointer.reg = 0xFFFE;

    //Zero out the rom data
    std::memset(m_Rom, 0, sizeof m_Rom);

    //Set initial rom program
    m_Rom[0xFF05] = 0x00;
    m_Rom[0xFF06] = 0x00;
    m_Rom[0xFF07] = 0x00;
    m_Rom[0xFF10] = 0x80;
    m_Rom[0xFF11] = 0xBF;
    m_Rom[0xFF12] = 0xF3;
    m_Rom[0xFF14] = 0xBF;
    m_Rom[0xFF16] = 0x3F;
    m_Rom[0xFF17] = 0x00;
    m_Rom[0xFF19] = 0xBF;
    m_Rom[0xFF1A] = 0x7F;
    m_Rom[0xFF1B] = 0xFF;
    m_Rom[0xFF1C] = 0x9F;
    m_Rom[0xFF1E] = 0xBF;
    m_Rom[0xFF20] = 0xFF;
    m_Rom[0xFF21] = 0x00;
    m_Rom[0xFF22] = 0x00;
    m_Rom[0xFF23] = 0xBF;
    m_Rom[0xFF24] = 0x77;
    m_Rom[0xFF25] = 0xF3;
    m_Rom[0xFF26] = 0xF1;
    m_Rom[0xFF40] = 0x91;
    m_Rom[0xFF42] = 0x00;
    m_Rom[0xFF43] = 0x00;
    m_Rom[0xFF45] = 0x00;
    m_Rom[0xFF47] = 0xFC;
    m_Rom[0xFF48] = 0xFF;
    m_Rom[0xFF49] = 0xFF;
    m_Rom[0xFF4A] = 0x00;
    m_Rom[0xFF4B] = 0x00;
    m_Rom[0xFFFF] = 0x00;

    //Clear the screen data
    ClearScreenData();
}

void Emulator::ClearScreenData()
{
    memset(m_ScreenData, 0, sizeof m_ScreenData);
}

Emulator::Emulator(sf::RenderWindow& window)
    : window(window)
{
    InitState();
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
