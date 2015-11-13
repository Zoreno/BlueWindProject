#pragma once

#include "GameWindow.h"
#include "World.h"

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
private:
	Game* gamePointer_;
	World* currentWorld_;
	std::vector<World*> worlds_;
};