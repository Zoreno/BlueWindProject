#pragma once

#include "Frame.h"

class Application;

class Menu : public Frame
{
public:
	Menu(Application*);

	void update() override;
	void render(GameWindow&) override;
};