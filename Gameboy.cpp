// Gameboy.cpp : Defines the entry point for the application.
//

#include "Gameboy.h"
#include "GBDef.h"
#include "Emulator.h"
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(256, 240), "Gameboy");
	window.setFramerateLimit(60);

	Emulator GB(window);

	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		GB.Update();
		window.display();
	}
}
