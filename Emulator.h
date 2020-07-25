#ifndef EMULATOR_H
#define EMULATOR_H

#include <SFML/Graphics.hpp>
#include "GBDef.h"

class Emulator
{
private:
	sf::RenderWindow& window;
	BYTE m_CartridgeMemory[0x200000];
	bool m_MBC1;
	bool m_MBC2;

	BYTE m_RAMBanks[0x8000];
	BYTE m_CurrentRAMBank;
	BYTE m_ScreenData[160][144][3];
	BYTE m_Rom[0x10000];

	union Register
	{
		WORD reg;
		struct
		{
			BYTE lo;
			BYTE hi;
		};
	};

	Register m_RegisterAF;
	Register m_RegisterBC;
	Register m_RegisterDE;
	Register m_RegisterHL;

	WORD m_ProgramCounter;
	Register m_StackPointer;

	BYTE m_CurrentROMBank;

	bool m_EnableRAM;
	bool m_ROMBanking;

	#define CLOCKSPEED 4194304
	int frequency = 4096;
	int m_TimerCounter = (CLOCKSPEED / frequency);
	int m_DividerCounter = 0;

	void InitState();
	void ClearScreenData();
public:
	explicit Emulator(sf::RenderWindow& window);
	int ExecuteNextOpcode();
	void UpdateTimers(int cycles);
	bool IsClockEnabled() const;
	BYTE GetClockFreq() const;
	void SetClockFreq();
	void DoDividerRegister(int cycles);
	void UpdateGraphics(int cycles);
	void DoInterupts();
	void RequestInterupt(int id);
	void LoadCart(const char* path);
	void WriteMemory(WORD address, BYTE data);
	BYTE ReadMemory(WORD address) const;
	void HandleBanking(WORD address, BYTE data);
	void DoRAMBankEnable(WORD address, BYTE data);
	void DoChangeLoROMBank(BYTE data);
	void DoChangeHiRomBank(BYTE data);
	void DoRAMBankChange(BYTE data);
	void DoChangeROMRAMMode(BYTE data);
	void Update();
	void RenderScreen();
};

#endif //EMULATOR_H