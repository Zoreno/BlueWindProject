#pragma once

#include<vector>
#include <string>
#include <SFML\Graphics.hpp>
#include "GameWindow.h"

class Entity;

class Animation
{
public:
	Animation(Entity*, sf::Texture&);
	Animation(const Animation&) = delete;
	Animation& operator=(const Animation&) = delete;

	void update(int,int, bool);
	void render(GameWindow&);
private:
	sf::Sprite currentSprite_;
	sf::Texture& texture_;

	int counter;
	int animState;

	Entity* entityPtr_;
};