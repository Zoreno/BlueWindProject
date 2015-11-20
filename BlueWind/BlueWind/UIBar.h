#pragma once

#include <SFML\Graphics.hpp>
#include "GameWindow.h"

class UIBar
{
public:
	UIBar() = delete;
	UIBar(UIBar&) = delete;
	UIBar& operator=(const UIBar&) = delete;

	void update(int, int);
	void render(GameWindow&);

private:
	float fillLevel_;
	sf::Vector2f size_;
	sf::Vector2f position_;
	sf::Color color_;
	std::string postfix_;
};