#pragma once

#include "GameWindow.h"
#include "FrameButton.h"
#include <stdexcept>

class Application;

class FrameException : public std::logic_error
{
public:
	using std::logic_error::logic_error;
};

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

	void addButton(sf::Vector2f, sf::Vector2f, std::string, std::string, std::function<void(Application*)>);
protected:
	std::vector<FrameButton*> buttons_;
	Application* appPointer_;
};