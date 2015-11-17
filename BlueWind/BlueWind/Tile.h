#pragma once

#include <string>
#include <SFML\Graphics.hpp>
#include "GameWindow.h"

//TODO fixa
class Tile
{
public:
	Tile(sf::Texture&, bool);

	void render(GameWindow&, int, int);

	sf::Sprite sprite_;
	bool walkable_;
	
};