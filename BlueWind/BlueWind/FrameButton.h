#pragma once

#include <SFML\Graphics.hpp>
#include <string>
#include "GameWindow.h"
#include <functional>

class Application;

class FrameButton
{
public:
	FrameButton(Application*,sf::Vector2f, std::string, sf::Vector2f, std::function<void (Application*)>);
	FrameButton(const FrameButton&) = delete;
	FrameButton& operator=(const FrameButton&) = delete;

	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;

	void update();
	void render(GameWindow&);
	void clicked();

private:
	Application* appPointer_;
	sf::Vector2f position_;
	sf::Vector2f size_;
	std::string file_;
	sf::Sprite sprite_;
	std::function<void(Application*)> callback_;
};
