#pragma once

#include "GameWindow.h"
#include "FrameButton.h"

class Application;

class Frame
{
public:
	Frame(Application*);
	Frame(const Frame&) = delete;
	Frame& operator=(const Frame&) = delete;

	virtual void update() = 0;
	virtual void render(GameWindow&) = 0;

	virtual void handleKeyEvent(sf::Event) = 0;
	virtual void handleMouseEvent(sf::Event) = 0;

	virtual ~Frame();

	void addButton(sf::Vector2f, std::string, sf::Vector2f, std::function<void(Application*)>);
protected:
	std::vector<FrameButton*> buttons_;
	Application* appPointer_;
};