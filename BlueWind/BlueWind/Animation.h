#pragma once

#include<vector>
#include <string>
#include <SFML\Graphics.hpp>
#include "GameWindow.h"

class Entity;

class Animation
{
public:
	enum STATES{walking, idle, attacking};
	enum DIRECTION{north, west, east, south};
	Animation(Entity*);
	Animation(const Animation&) = delete;
	Animation& operator=(const Animation&) = delete;

	void update();
	void render(GameWindow&);
	void loadTexture(const std::string&, const std::string&, std::vector<sf::Texture*>&);

	sf::Sprite currentSprite_;
	std::vector<sf::Texture*> walkingWest_;
	std::vector<sf::Texture*> walkingEast_;
	std::vector<sf::Texture*> walkingNorth_;
	std::vector<sf::Texture*> walkingSouth_;
	std::vector<sf::Texture*> idle_;
	std::vector<sf::Texture*> attackingWest_;
	std::vector<sf::Texture*> attackingEast_;
	std::vector<sf::Texture*> attackingNorth_;
	std::vector<sf::Texture*> attackingSouth_;

	int it{ 0 };
	int cooldown{ 0 };
	STATES state_{ idle };
	DIRECTION dir_{ south };

	Entity* entityPtr_;
};