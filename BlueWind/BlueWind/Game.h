#pragma once

#include <string>
#include "Frame.h"
#include "GameWindow.h"
#include "TextureHandler.h"
#include "Universe.h"
#include "Player.h"
#include "UserInterface.h"

class GameState
{
public:
	bool bridge1Built{ false };
	bool minotaurDead{ false };
	bool bridge2Built{ false };

	std::string toString();
};

class Game : public Frame
{
public:
	Game(Application*, bool = false);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	
	void update() override;
	void render(GameWindow&) override;

	void handleKeyEvent(sf::Event) override;
	void handleMouseEvent(sf::Event) override;

	void saveGame();
	void loadGame();

	Player* getPlayer();
	Application* getApp();
	UserInterface* getUserInterface();
	GameState* getGameState();
	sf::Texture& getTexture(const std::string&);
private:
	TextureHandler textureHandler_;
	Universe universe_;
	Player player_;
	UserInterface ui_;
	GameState gameState_;
};