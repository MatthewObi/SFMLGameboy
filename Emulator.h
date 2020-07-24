#ifndef EMULATOR_H
#define EMULATOR_H

#include <SFML/Graphics.hpp>
#include "GBCart.h"

class Emulator
{
private:
	sf::RenderWindow& window;
	GBCart cart;
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

	void InitState();
	void ClearScreenData();
public:
	explicit Emulator(sf::RenderWindow& window);
	int ExecuteNextOpcode();
	void UpdateTimers(int cycles);
	void UpdateGraphics(int cycles);
	void DoInterupts();
	void Update();
	void RenderScreen();
};

#endif //EMULATOR_H