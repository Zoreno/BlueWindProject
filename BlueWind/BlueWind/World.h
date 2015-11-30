#pragma once

#include "GameWindow.h"
#include <string>
#include "Enemy.h"
#include "NPC.h"
#include <map>

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
	void removeEnemy(Enemy*);
	void removeNPC(NPC*);
	void changeTile(int, int);

	Universe* getUniverse() const;

	const int getID() const;
	const int getMapWidth() const;
	const int getMapHeight() const;
	const std::vector<int> getTileVector() const;
	const std::map<int,Enemy*> getEnemyVector() const;
	const std::map<int,NPC*> getNPCVector() const;
private:
	std::vector<int> tileVector_;
	const int ID_;
	Universe* universePointer_;

	std::map<int,Enemy*> enemyVector_;
	std::vector<int> removeEnemyVector_;
	std::map<int,NPC*> NPCVector_;
	std::vector<int> remoneNPCVector_;

	int mapWidth;
	int mapHeight;

	int getIntFromColor(sf::Color);

	void updateLists();
};