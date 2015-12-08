#pragma once

#include <map>
#include "GameWindow.h"
#include "FrameButton.h"

class Input
{
public:
	Input(Application*);
	Input(const Input&) = delete;
	Input() = delete;
	Input& operator=(const Input&) = delete;
	
	bool isPressed(char) const;
	
	void update();

	void keyPressed(sf::Event);
	void mousePressed(sf::Event);

private:
	Application* appPointer_;
	std::map<char, bool> pressedButtons_;
};