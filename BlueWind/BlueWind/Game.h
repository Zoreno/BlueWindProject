#pragma once

#include "Frame.h"
#include "GameWindow.h"

class Game : public Frame
{
public:
	Game(Application*);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	
	void update() override;
	void render(GameWindow&) override;;
private:

};