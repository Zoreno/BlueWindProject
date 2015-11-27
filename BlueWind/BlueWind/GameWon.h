#pragma once

#include "Frame.h"
#include "GameWindow.h"

class Application;

class GameWon : public Frame
{
public:
	GameWon(Application*);
	GameWon(const GameWon&) = delete;
	GameWon& operator=(const GameWon&) = delete;

	void handleKeyEvent(sf::Event) override;
	void handleMouseEvent(sf::Event) override;

	void update() override;
	void render(GameWindow&) override;

private:
	sf::Sprite background_;
};
