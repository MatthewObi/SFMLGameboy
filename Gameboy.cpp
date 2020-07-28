// Gameboy.cpp : Defines the entry point for the application.
//

#include "Gameboy.h"
#include "GBDef.h"
#include "Emulator.h"
#include <SFML/Graphics.hpp>

using namespace std;

constexpr char* testRom = "TESTspec.gb";

constexpr sf::Keyboard::Key keyBindings[] =
{
	sf::Keyboard::Right, //BUTTON_RIGHT
	sf::Keyboard::Left, //BUTTON_LEFT
	sf::Keyboard::Up, //BUTTON_UP
	sf::Keyboard::Down, //BUTTON_DOWN
	sf::Keyboard::Z, //BUTTON_A
	sf::Keyboard::X, //BUTTON_B
	sf::Keyboard::A, //BUTTON_SELECT
	sf::Keyboard::S, //BUTTON_START
};

void DrawInput(sf::RenderWindow& window)
{
	for (int i = 0; i < 8; i++)
	{
		sf::RectangleShape shape;
		shape.setSize(sf::Vector2f(8, 8));
		shape.setPosition(sf::Vector2f(i * 8, 0));
		switch (i) {
		case BUTTON_A:
			shape.setFillColor(sf::Color::Red);
			break;
		case BUTTON_B:
			shape.setFillColor(sf::Color::Blue);
			break;
		case BUTTON_START:
			shape.setFillColor(sf::Color::Yellow);
			break;
		case BUTTON_SELECT:
			shape.setFillColor(sf::Color::Green);
			break;
		case BUTTON_RIGHT:
		case BUTTON_LEFT:
		case BUTTON_UP:
		case BUTTON_DOWN:
			shape.setFillColor(sf::Color::Black);
			break;
		}
		if (sf::Keyboard::isKeyPressed(keyBindings[i]))
			window.draw(shape);
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(160, 144), "Gameboy");
	window.setFramerateLimit(60);

	Emulator* GB = new Emulator(window);
	GB->LoadCart(testRom);
	//GB->LoadCart("Tetris.gb");

	window.clear(sf::Color::White);
	window.display();

	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			switch (e.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				switch (e.key.code) {
				case keyBindings[BUTTON_A]:
					GB->KeyPressed(BUTTON_A);
					break;
				case keyBindings[BUTTON_B]:
					GB->KeyPressed(BUTTON_B);
					break;
				case keyBindings[BUTTON_SELECT]:
					GB->KeyPressed(BUTTON_SELECT);
					break;
				case keyBindings[BUTTON_START]:
					GB->KeyPressed(BUTTON_START);
					break;
				case keyBindings[BUTTON_RIGHT]:
					GB->KeyPressed(BUTTON_RIGHT);
					break;
				case keyBindings[BUTTON_LEFT]:
					GB->KeyPressed(BUTTON_LEFT);
					break;
				case keyBindings[BUTTON_UP]:
					GB->KeyPressed(BUTTON_UP);
					break;
				case keyBindings[BUTTON_DOWN]:
					GB->KeyPressed(BUTTON_DOWN);
					break;
				}
				break;
			case sf::Event::KeyReleased:
				switch (e.key.code) {
				case keyBindings[BUTTON_A]:
					GB->KeyReleased(BUTTON_A);
					break;
				case keyBindings[BUTTON_B]:
					GB->KeyReleased(BUTTON_B);
					break;
				case keyBindings[BUTTON_SELECT]:
					GB->KeyReleased(BUTTON_SELECT);
					break;
				case keyBindings[BUTTON_START]:
					GB->KeyReleased(BUTTON_START);
					break;
				case keyBindings[BUTTON_RIGHT]:
					GB->KeyReleased(BUTTON_RIGHT);
					break;
				case keyBindings[BUTTON_LEFT]:
					GB->KeyReleased(BUTTON_LEFT);
					break;
				case keyBindings[BUTTON_UP]:
					GB->KeyReleased(BUTTON_UP);
					break;
				case keyBindings[BUTTON_DOWN]:
					GB->KeyReleased(BUTTON_DOWN);
					break;
				}
				break;
			}
		}
		window.clear();
		GB->Update();
		DrawInput(window);
		window.display();
	}

	delete GB;
}
