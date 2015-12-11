#pragma once

#include "GameWindow.h"
#include "World.h"
#include "Tile.h"
#include <map>
#include "Enemy.h"
#include "NPC.h"
#include "Sensor.h"
#include <stdexcept>

class Game;

class UniverseException : public std::logic_error
{
public:
	using std::logic_error::logic_error;
};

class Universe
{
public:
	Universe(Game*);
	Universe(const Universe&) = delete;
	Universe& operator=(const Universe&) = delete;

	~Universe();

	void update();
	void render(GameWindow&);
	World* getCurrentWorld();
	World* getWorld(int);
	void setCurrentWorld(int);

	void switchWorld(int, int, int);

	Tile& getTile(int);

	Game* getGame() const;

	void addEnemy(int, Enemy*);
	void addNPC(int, NPC*);
	void addSensor(int, Sensor*);

	void populateCity();

private:
	Game* gamePointer_;
	World* currentWorld_;
	std::vector<World*> worlds_;
	std::map<int, Tile*> tileAtlas_;

	void loadTiles();
	void loadWorlds();
	void populateWorlds();
	
};