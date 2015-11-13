#pragma once

#include "GameWindow.h"

class Universe;

class World
{
public:
	World(int, Universe*);
	World() = delete;
	World(const World&) = delete;
	World& operator=(const World&) = delete;

	void update();
	void render(GameWindow&);

	const int getID() const;
private:
	const int ID_;
	Universe* universePointer_;
};