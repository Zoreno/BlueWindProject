#pragma once

#include <string>
#include <SFML\Graphics.hpp>
#include "GameWindow.h"

class Tile
{
public:
	Tile(sf::Texture&, bool);

	void render(GameWindow&, int, int);

	static const int TILESIZE{ 32 };

	bool isWalkable();
private:
	sf::Sprite sprite_;
	bool walkable_;
};