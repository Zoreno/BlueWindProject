#pragma once

#include "Frame.h"
#include "GameWindow.h"
#include "TextureHandler.h"
#include "Universe.h"
#include <string>
#include "Player.h"

class Game : public Frame
{
public:
	Game(Application*);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	
	void update() override;
	void render(GameWindow&) override;

	sf::Texture& getTexture(const std::string&);
private:
	TextureHandler textureHandler_;
	Universe universe_;
	Player player_;
};