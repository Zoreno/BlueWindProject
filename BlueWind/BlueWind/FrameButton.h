#pragma once

#include <SFML\Graphics.hpp>
#include <string>
#include "GameWindow.h"

class Application;

class FrameButton
{
public:
	FrameButton(Application*,sf::Vector2f, std::string);
	FrameButton(const FrameButton&) = delete;
	FrameButton& operator=(const FrameButton&) = delete;

	sf::Vector2f getPosition() const;

	void update();
	void render(GameWindow&);

private:
	Application* appPointer_;
	sf::Vector2f position_;
	sf::Sprite sprite_;
	std::string file_;
};