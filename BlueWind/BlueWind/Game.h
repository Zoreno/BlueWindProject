#pragma once

#include "Frame.h"
#include "GameWindow.h"
#include "TextureHandler.h"
#include "Universe.h"
#include <string>
#include "Player.h"
#include "UserInterface.h"

class Game : public Frame
{
public:
	Game(Application*);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	
	void update() override;
	void render(GameWindow&) override;

	Player* getPlayer();
	Application* getApp();
	sf::Texture& getTexture(const std::string&);
private:
	TextureHandler textureHandler_;
	Universe universe_;
	Player player_;
	UserInterface ui_;
};