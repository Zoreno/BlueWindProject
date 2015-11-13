#pragma once

#include "GameWindow.h"
#include "FrameButton.h"

class Application;

class Frame
{
public:
	Frame(Application*);
	virtual void update() = 0;
	virtual void render(GameWindow&) = 0;

	void addButton(FrameButton);
protected:
	std::vector<FrameButton> buttons_;
	Application* appPointer_;
};