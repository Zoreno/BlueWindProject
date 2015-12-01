#include "Universe.h"
#include "Game.h"
#include "World.h" 
#include "Tile.h"
#include "Application.h"
#include "GameWon.h"
#include <iostream>

using namespace std;

Universe::Universe(Game * gamePtr)
	: gamePointer_{gamePtr}
{
	loadTiles();
	loadWorlds();
	populateWorlds();
}

void Universe::update()
{
	currentWorld_->update();
}

void Universe::render(GameWindow & window)
{
	currentWorld_->render(window);
}

World * Universe::getCurrentWorld()
{
	return currentWorld_;
}

World * Universe::getWorld(int ID)
{
	for (auto it : worlds_)
	{
		if (ID == it->getID())
		{
			return it;
		}
	}
	//TODO kasta ex
	return nullptr;
}

void Universe::setCurrentWorld(int ID)
{
	for (auto it : worlds_)
	{
		if (ID == it->getID())
		{
			currentWorld_ = it;
		}
	}
}

void Universe::switchWorld(int ID, int x, int y)
{
	setCurrentWorld(ID);
	gamePointer_->getPlayer()->teleport(x, y);
	gamePointer_->getPlayer()->setCurrentWorld(currentWorld_);
}

Tile Universe::getTile(int i)
{
	return (*tileAtlas_.find(i)->second);
}

Game * Universe::getGame() const
{
	return gamePointer_;
}

void Universe::loadTiles()
{
	cout << "Laddar in Tiles" << endl;
	tileAtlas_.emplace(0,new Tile(gamePointer_->getTexture("grass"), true));
	tileAtlas_.emplace(1,new Tile(gamePointer_->getTexture("tree"), false));
	tileAtlas_.emplace(2, new Tile(gamePointer_->getTexture("bridge"), true));
	cout << "Laddning av tiles klart" << endl;
}

void Universe::loadWorlds()
{
	cout << "Laddar in världar" << endl;
	worlds_.push_back(new World(0, this, "res/worlds/level.bmp"));
	worlds_.push_back(new World(1, this, "res/worlds/level2.bmp"));

	cout << "Laddning av världar klart" << endl;

	setCurrentWorld(0);
}

void Universe::populateWorlds() 
{
	void PaulInteract(World*);
	void ErwinInteract(World*);
	void JamesClerkInteract(World*);

	void SensorseiInteract(World*);

	//OBS!!!!!!
	//UNIKA ID KRÄVS
	addNPC(0, new NPC(1, 100, 10, 0, "Paul", sf::Vector2f(3 * Tile::TILESIZE, 10 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("NPC"), "Here comes the dirac train!", PaulInteract));
	addNPC(1, new NPC(1, 100, 10, 1, "Erwin", sf::Vector2f(10 * Tile::TILESIZE, 5 * Tile::TILESIZE), getWorld(1), gamePointer_->getTexture("NPC"), "Hej, jag heter Erwin!", ErwinInteract));
	addNPC(0, new NPC(1, 100, 10, 2, "James Clerk", sf::Vector2f(10 * Tile::TILESIZE, 3 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("NPC"), "Hej, jag heter James Clerk!", JamesClerkInteract));
	//--------------------------
	addEnemy(0, new Enemy(1, 100, 10, 0, "Pelle", sf::Vector2f(12 * Tile::TILESIZE, 14 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("enemy")));
	addEnemy(0, new Enemy(1, 100, 10, 1, "Pelle", sf::Vector2f(13 * Tile::TILESIZE, 14 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("enemy")));
	addEnemy(0, new Enemy(1, 100, 10, 2, "Pelle", sf::Vector2f(14 * Tile::TILESIZE, 14 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("enemy")));

	addSensor(1, new Sensor(0, "Sensorsei", sf::Vector2f(1 * Tile::TILESIZE, 0 * Tile::TILESIZE), getWorld(1), SensorseiInteract, gamePointer_->getTexture("enemy")));

}

void Universe::addEnemy(int worldID, Enemy * enemyPtr)
{
	for (auto it : worlds_)
	{
		if (it->getID() == worldID)
		{
			it->addEnemy(enemyPtr);
			break;
		}
	}
}

void Universe::addNPC(int worldID, NPC * NPCPtr)
{
	for (auto it : worlds_)
	{
		if (it->getID() == worldID)
		{
			it->addNPC(NPCPtr);
			break;
		}
	}
}

void Universe::addSensor(int worldID, Sensor* sensorPtr)
{
	for (auto it : worlds_)
	{
		if (it->getID() == worldID)
		{
			it->addSensor(sensorPtr);
			break;
		}
	}
}

void PaulInteract(World* worldPtr)
{
	worldPtr->getUniverse()->getGame()->getApp()->getSoundHandler().playSound("diracTrain");

	for (int i = 0; i < 6; ++i)
	{
		worldPtr->changeTile((6 * worldPtr->getMapWidth() + 15 + i), 2);
		worldPtr->changeTile((7 * worldPtr->getMapWidth() + 15 + i), 2);
	}
}

void ErwinInteract(World* worldPtr)
{
	worldPtr->getUniverse()->getGame()->getApp()->setNextFrame(new GameWon(worldPtr->getUniverse()->getGame()->getApp()));
}

void JamesClerkInteract(World* worldPtr)
{
	worldPtr->getUniverse()->switchWorld(1, 64, 64);
}

void SensorseiInteract(World* worldPtr)
{
	worldPtr->getUniverse()->switchWorld(0, 64, 64);
}