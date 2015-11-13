#pragma once

#include <SFML\Graphics.hpp>
#include <string>
#include "GameWindow.h"

class FrameButton
{
public:
	FrameButton(sf::Vector2f, sf::Vector2f, std::string);
	FrameButton(const FrameButton&) = delete;
	FrameButton& operator=(const FrameButton&) = delete;

	sf::Vector2f getPosition() const;

	void update();
	void render(GameWindow&);

private:
	sf::Vector2f size_;
	sf::Vector2f position_;
	std::string text_;
};