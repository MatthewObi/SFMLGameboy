#ifndef EMULATOR_H
#define EMULATOR_H

#include <SFML/Graphics.hpp>

class Emulator
{
private:
	sf::RenderWindow& window;
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