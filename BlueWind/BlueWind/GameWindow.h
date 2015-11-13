#pragma once

#include <SFML\Graphics.hpp>
#include <string>

class GameWindow : public sf::RenderWindow
{
public:
	GameWindow(sf::VideoMode, std::string);
	GameWindow(const GameWindow&) = delete;
	GameWindow& operator=(const GameWindow&) = delete;
};