#pragma once

#include "GameWindow.h"
#include <string>
#include "Enemy.h"
#include "NPC.h"

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
	void addNPC(NPC*);
	//TODO remove enemy

	Universe* getUniverse() const;

	const int getID() const;
	const int getMapWidth() const;
	const int getMapHeight() const;
	const std::vector<int> getTileVector() const;
private:
	std::vector<int> tileVector_;
	const int ID_;
	Universe* universePointer_;

	std::vector<Enemy*> enemyVector_;
	std::vector<NPC*> NPCVector_;

	int mapWidth;
	int mapHeight;

	int getIntFromColor(sf::Color);
};