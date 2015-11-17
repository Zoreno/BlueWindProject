#pragma once

#include "GameWindow.h"
#include <string>

class Universe;

class World
{
public:
	World(int, Universe*, std::string);
	World() = delete;
	World(const World&) = delete;
	World& operator=(const World&) = delete;

	void update();
	void render(GameWindow&);

	void loadWorld(std::string);

	const int getID() const;
private:
	std::vector<int> tileVector_;
	const int ID_;
	Universe* universePointer_;

	int mapWidth;
	int mapHeight;

	int getIntFromColor(sf::Color);
};