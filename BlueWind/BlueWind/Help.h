#pragma once

#include "Frame.h"
#include "GameWindow.h"

class Application;

class Help : public Frame
{
public:
	Help(Application*);
	Help(const Help&) = delete;
	Help& operator=(const Help&) = delete;

	void handleKeyEvent(sf::Event) override;
	void handleMouseEvent(sf::Event) override;

	void update() override;
	void render(GameWindow&) override;

private:
	sf::Sprite background_;
};
