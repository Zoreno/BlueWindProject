#pragma once

#include "Frame.h"
#include "GameWindow.h"

class Game : public Frame
{
public:
	Game(Application*);
	
	void update() override;
	void render(GameWindow&) override;;
private:

};