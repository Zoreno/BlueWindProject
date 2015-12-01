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
	
	std::map<char, bool> pressedButtons_; // TODO lägg private och skapa en get-funtkion
	void update();

	void keyPressed(sf::Event);
	void mousePressed(sf::Event);

private:
	Application* appPointer_;
};