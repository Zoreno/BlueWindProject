#pragma once

#include <SFML\Graphics.hpp>
#include "GameWindow.h"
#include "UserInterface.h"

class UIBar
{
public:
	UIBar(sf::Vector2f, sf::Vector2f, sf::Color, std::string, UserInterface*);
	UIBar() = delete;
	UIBar(UIBar&) = delete;
	UIBar& operator=(const UIBar&) = delete;

	void update(float, float);
	void render(GameWindow&);

private:
	float fillLevel_;
	sf::Vector2f size_;
	sf::Vector2f position_;
	sf::Color color_;
	std::string postfix_;
	std::string text_;

	UserInterface* ui_;
};