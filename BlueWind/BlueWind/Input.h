#pragma once

#include <map>
#include "GameWindow.h"
#include "FrameButton.h"

class Input
{
public:
	Input(Application*);
	// TODO delete:a konstruktorer
	
	std::map<char, bool> pressedButtons_; // TODO lägg private och skapa en get-funtkion
	void update();

	void keyPressed(sf::Event);

private:
	Application* appPointer_;
};