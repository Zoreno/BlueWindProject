#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include "GameWindow.h"
#include "Menu.h"
#include "Game.h"
#include "Input.h"
#include "SoundHandler.h"

class Application
{
public:
	Application();
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;

	void run();

	void render(GameWindow& window);
	void update();
	const Input getInput();
	Frame* getCurrentFrame();
	void startGame();

	const sf::Font& getFont() const;
	GameWindow& getGameWindow();
	SoundHandler& getSoundHandler();
private:
	GameWindow window_{ sf::VideoMode(800, 600), "SFML doesnt work!" };
	Frame* currentFrame_;
	sf::Font font_;
	Input input_;
	SoundHandler soundHandler_;
};