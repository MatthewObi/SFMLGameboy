#ifndef EMULATOR_H
#define EMULATOR_H

#include <SFML/Graphics.hpp>
#include "GBDef.h"

class Emulator
{
private:
	sf::RenderWindow& window;
	sf::Image image;
	sf::Texture t;
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
	BYTE lcdControl;
	BYTE m_JoypadState;

	WORD m_ProgramCounter;
	Register m_StackPointer;

	BYTE m_CurrentROMBank = 1;

	bool m_EnableRAM;
	bool m_ROMBanking;

	#define CLOCKSPEED 4194304
	int frequency = 4096;
	int m_TimerCounter = (CLOCKSPEED / frequency);
	int m_DividerCounter = 0;

	bool m_InteruptMaster = false;
	int m_ScanlineCounter = 0;
	bool m_WaitForJoypad = false;
	bool m_WaitForInterupt = false;

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
	void SetLCDStatus();
	bool IsLCDEnabled() const;
	void DrawScanLine();
	void RenderTiles();
	void RenderSprites();
	COLOR GetColor(BYTE colorNum, WORD address) const;
	void DoInterupts();
	void RequestInterupt(int id);
	void ServiceInterupt(int interupt);
	void PushWordOntoStack(WORD word);
	WORD PopWordOffStack();
	void LoadCart(const char* path);
	void WriteMemory(WORD address, BYTE data);
	void WriteWord(WORD address, WORD data);
	BYTE ReadMemory(WORD address) const;
	WORD ReadWord() const;
	void HandleBanking(WORD address, BYTE data);
	void DoRAMBankEnable(WORD address, BYTE data);
	void DoChangeLoROMBank(BYTE data);
	void DoChangeHiRomBank(BYTE data);
	void DoRAMBankChange(BYTE data);
	void DoChangeROMRAMMode(BYTE data);
	void DoDMATransfer(BYTE data);
	void KeyPressed(int key);
	void KeyReleased(int key);
	BYTE GetJoypadState() const;
	void Update();
	void RenderScreen();
};

#endif //EMULATOR_H