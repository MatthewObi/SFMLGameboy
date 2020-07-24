#include "Emulator.h"
#include "GBUtil.h"

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
    m_CurrentROMBank = 1;
    std::memset(&m_CartridgeMemory, 0, sizeof(m_CartridgeMemory));
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

void Emulator::LoadCart(const char* path)
{
    FILE* f;
    f = fopen(path, "rb");
    fread(m_CartridgeMemory, 1, sizeof m_CartridgeMemory, f);
    fclose(f);

    m_MBC1 = false;
    m_MBC2 = false;

    switch (m_CartridgeMemory[0x147])
    {
    case 1: m_MBC1 = true; break;
    case 2: m_MBC1 = true; break;
    case 3: m_MBC1 = true; break;
    case 5: m_MBC2 = true; break;
    case 6: m_MBC2 = true; break;
    default: break;
    }

    memset(&m_RAMBanks, 0, sizeof(m_RAMBanks));
    m_CurrentRAMBank = 0;
}

void Emulator::WriteMemory(WORD address, BYTE data)
{
    if (address < 0x8000)
    {
        HandleBanking(address, data);
    }

    else if ((address >= 0xA000) && (address < 0xC000))
    {
        if (m_EnableRAM)
        {
            WORD newAddress = address - 0xA000;
            m_RAMBanks[newAddress + (m_CurrentRAMBank * 0x2000)] = data;
        }
    }

    // writing to ECHO ram also writes in RAM
    else if ((address >= 0xE000) && (address < 0xFE00))
    {
        m_Rom[address] = data;
        WriteMemory(address - 0x2000, data);
    }

    // this area is restricted
    else if ((address >= 0xFEA0) && (address < 0xFEFF))
    {
    }

    // no control needed over this area so write to memory
    else
    {
        m_Rom[address] = data;
    }
}

BYTE Emulator::ReadMemory(WORD address) const
{
    // are we reading from the rom memory bank?
    if ((address >= 0x4000) && (address <= 0x7FFF))
    {
        WORD newAddress = address - 0x4000;
        return m_CartridgeMemory[newAddress + (m_CurrentROMBank * 0x4000)];
    }

    // are we reading from ram memory bank?
    else if ((address >= 0xA000) && (address <= 0xBFFF))
    {
        WORD newAddress = address - 0xA000;
        return m_RAMBanks[newAddress + (m_CurrentRAMBank * 0x2000)];
    }

    return m_Rom[address];
}

void Emulator::HandleBanking(WORD address, BYTE data)
{
    // do RAM enabling
    if (address < 0x2000)
    {
        if (m_MBC1 || m_MBC2)
        {
            DoRAMBankEnable(address, data);
        }
    }

    // do ROM bank change
    else if ((address >= 0x200) && (address < 0x4000))
    {
        if (m_MBC1 || m_MBC2)
        {
            DoChangeLoROMBank(data);
        }
    }

    // do ROM or RAM bank change
    else if ((address >= 0x4000) && (address < 0x6000))
    {
        // there is no rambank in mbc2 so always use rambank 0
        if (m_MBC1)
        {
            if (m_ROMBanking)
            {
                DoChangeHiRomBank(data);
            }
            else
            {
                DoRAMBankChange(data);
            }
        }
    }

    // this will change whether we are doing ROM banking
    // or RAM banking with the above if statement
    else if ((address >= 0x6000) && (address < 0x8000))
    {
        if (m_MBC1)
            DoChangeROMRAMMode(data);
    }
}

void Emulator::DoRAMBankEnable(WORD address, BYTE data)
{
    if (m_MBC2)
    {
        if (TestBit(address, 4) == 1) return;
    }

    BYTE testData = data & 0xF;
    if (testData == 0xA)
        m_EnableRAM = true;
    else if (testData == 0x0)
        m_EnableRAM = false;
}

void Emulator::DoChangeLoROMBank(BYTE data)
{
    if (m_MBC2)
    {
        m_CurrentROMBank = data & 0xF;
        if (m_CurrentROMBank == 0) m_CurrentROMBank++;
        return;
    }

    const BYTE lower5 = data & 31;
    m_CurrentROMBank &= 224; // turn off the lower 5
    m_CurrentROMBank |= lower5;
    if (m_CurrentROMBank == 0) m_CurrentROMBank++;
}

void Emulator::DoChangeHiRomBank(BYTE data)
{
    // turn off the upper 3 bits of the current rom
    m_CurrentROMBank &= 31;

    // turn off the lower 5 bits of the data
    data &= 224;
    m_CurrentROMBank |= data;
    if (m_CurrentROMBank == 0) m_CurrentROMBank++;
}

void Emulator::DoRAMBankChange(BYTE data)
{
    m_CurrentRAMBank = data & 0x3;
}

void Emulator::DoChangeROMRAMMode(BYTE data)
{
    BYTE newData = data & 0x1;
    m_ROMBanking = (newData == 0) ? true : false;
    if (m_ROMBanking)
        m_CurrentRAMBank = 0;
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
