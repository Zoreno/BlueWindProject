#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include "GameWindow.h"

class Application
{
public:
	Application();
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;

	void run();

	void render(GameWindow& window);
	void update();
private:
	GameWindow window_{ sf::VideoMode(800, 600), "SFML doesnt work!" };

};