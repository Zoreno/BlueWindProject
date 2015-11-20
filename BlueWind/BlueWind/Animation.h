#pragma once

#include<vector>
#include "SFML\Graphics.hpp"

class Entity;

class Animation
{
public:
	enum STATES{walkingWest, walkingEast, walkingNorth, walkingSouth, idle, attackingWest, attackingEast, attackingNorth, attackingSouth};

	Animation() = delete;
	Animation(const Animation&) = delete;
	Animation& operator=(const Animation&) = delete;

	void update();
	void render(GameWindow&);

	sf::Sprite currentSprite_;
	std::vector<sf::Sprite> walkingWest_;
	std::vector<sf::Sprite> walkingEast_;
	std::vector<sf::Sprite> walkingNorth_;
	std::vector<sf::Sprite> walkingSouth_;
	std::vector<sf::Sprite> idle_;
	std::vector<sf::Sprite> attackingWest_;
	std::vector<sf::Sprite> attackingEast_;
	std::vector<sf::Sprite> attackingNorth_;
	std::vector<sf::Sprite> attackingSouth_;

	STATES state_{ idle };

	Entity* entityPtr_;
};