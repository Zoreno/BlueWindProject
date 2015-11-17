#pragma once

#include "GameWindow.h"
#include "World.h"
#include "Tile.h"
#include <map>

class Game;

class Universe
{
public:
	Universe(Game*);
	Universe(const Universe&) = delete;
	Universe& operator=(const Universe&) = delete;

	void update();
	void render(GameWindow&);
	World* getCurrentWorld();
	void setCurrentWorld(int);

	Tile getTile(int);

private:
	Game* gamePointer_;
	World* currentWorld_;
	std::vector<World*> worlds_;
	std::map<int, Tile*> tileAtlas_;

	void loadTiles();
	void loadWorlds();
};