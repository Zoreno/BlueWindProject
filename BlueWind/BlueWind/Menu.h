#pragma once

#include "Frame.h"
#include "GameWindow.h"

class Application;

class Menu : public Frame
{
public:
	Menu(Application*);
	Menu(const Menu&) = delete;
	Menu& operator=(const Menu&) = delete;

	void update() override;
	void render(GameWindow&) override;

private:
	sf::Sprite background_;
};