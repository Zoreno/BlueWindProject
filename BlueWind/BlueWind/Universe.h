#pragma once

#include "GameWindow.h"
#include "World.h"
#include "Tile.h"
#include <map>
#include "Enemy.h"
#include "NPC.h"
#include "Sensor.h"

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
	World* getWorld(int);
	void setCurrentWorld(int);

	void switchWorld(int, int, int);

	//TODO returnera pekare istället för att kopiera.
	Tile getTile(int);

	Game* getGame() const;

private:
	Game* gamePointer_;
	World* currentWorld_;
	std::vector<World*> worlds_;
	std::map<int, Tile*> tileAtlas_;

	void loadTiles();
	void loadWorlds();
	void populateWorlds();

	void addEnemy(int, Enemy*);
	void addNPC(int, NPC*);
	void addSensor(int, Sensor*);
};