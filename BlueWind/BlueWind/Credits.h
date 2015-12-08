#pragma once

#include "Frame.h"
#include "GameWindow.h"

class Application;

class Credits : public Frame
{
public:
	Credits(Application*);
	Credits(const Credits&) = delete;
	Credits& operator=(const Credits&) = delete;

	void handleKeyEvent(sf::Event) override;
	void handleMouseEvent(sf::Event) override;

	void update() override;
	void render(GameWindow&) override;

private:
	sf::Sprite background_;
};