#pragma once

#include "GameWindow.h"
#include <string>
#include "Enemy.h"

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
	void addEnemy(Enemy*);
	//TODO remove enemy

	Universe* getUniverse() const;

	const int getID() const;
private:
	std::vector<int> tileVector_;
	const int ID_;
	Universe* universePointer_;

	std::vector<Enemy*> enemyVector_;

	int mapWidth;
	int mapHeight;

	int getIntFromColor(sf::Color);
};