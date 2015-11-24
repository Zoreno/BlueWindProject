#pragma once

#include <SFML\Graphics.hpp>
#include <string>
#include "GameWindow.h"
#include <functional>

class Application;

class FrameButton
{
public:
	FrameButton(Application*,sf::Vector2f, sf::Vector2f, std::string, std::string, std::function<void (Application*)>);
	FrameButton(const FrameButton&) = delete;
	FrameButton& operator=(const FrameButton&) = delete;

	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;

	void update();
	void render(GameWindow&);
	void clicked();
	bool mouseOnButton(sf::Vector2i);

private:
	Application* appPointer_;
	sf::Vector2f position_;
	sf::Vector2f size_;
	sf::Texture normalTexture;
	sf::Texture hoverTexture;
	sf::Sprite sprite_;
	std::function<void(Application*)> callback_;
};