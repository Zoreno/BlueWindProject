#pragma once

#include "Frame.h"
#include "GameWindow.h"

class Application;

class GameOver : public Frame
{
public:
	GameOver(Application*);
	GameOver(const GameOver&) = delete;
	GameOver& operator=(const GameOver&) = delete;

	void handleKeyEvent(sf::Event) override;
	void handleMouseEvent(sf::Event) override;

	void update() override;
	void render(GameWindow&) override;

private:
	sf::Sprite background_;
};