#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include "GameWindow.h"

class Application
{
public:
	Application();

	void run();

	void render(GameWindow& window);
	void update();
private:
	GameWindow window{ sf::VideoMode(800, 600), "SFML doesnt work!" };

};