#include "Universe.h"
#include "Game.h"
#include "World.h" 
#include "Tile.h"
#include "Application.h"
#include "GameWon.h"
#include "NPC.h"
#include <iostream>

using namespace std;

Universe::Universe(Game * gamePtr)
	: gamePointer_{gamePtr}
{
	loadTiles();
	loadWorlds();
	populateWorlds();
}

Universe::~Universe()
{
	gamePointer_ = nullptr;
	currentWorld_ = nullptr;

	while (!worlds_.empty())
	{
		delete worlds_.back();
		worlds_.pop_back();
	}

	while (!tileAtlas_.empty())
	{
		auto it = tileAtlas_.begin();
		delete it->second;
		tileAtlas_.erase(it);
	}
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
	tileAtlas_.emplace(-1, new Tile(gamePointer_->getTexture("void"), true));
	tileAtlas_.emplace(0,new Tile(gamePointer_->getTexture("grass"), true));
	tileAtlas_.emplace(1,new Tile(gamePointer_->getTexture("tree"), false));
	tileAtlas_.emplace(2, new Tile(gamePointer_->getTexture("bridge"), true));
	tileAtlas_.emplace(3, new Tile(gamePointer_->getTexture("house00"), false));
	tileAtlas_.emplace(4, new Tile(gamePointer_->getTexture("house10"), false));
	tileAtlas_.emplace(5, new Tile(gamePointer_->getTexture("house01"), false));
	tileAtlas_.emplace(6, new Tile(gamePointer_->getTexture("house11"), false));
	tileAtlas_.emplace(7, new Tile(gamePointer_->getTexture("mountainGrass"), false));
	tileAtlas_.emplace(8, new Tile(gamePointer_->getTexture("water"), false));
	tileAtlas_.emplace(9, new Tile(gamePointer_->getTexture("stump"), true));
	cout << "Laddning av tiles klart" << endl;
}

void Universe::loadWorlds()
{
	cout << "Laddar in världar" << endl;
	worlds_.push_back(new World(0, this, "res/worlds/world1.bmp"));
	worlds_.push_back(new World(1, this, "res/worlds/level.bmp"));
	worlds_.push_back(new World(2, this, "res/worlds/level2.bmp"));

	cout << "Laddning av världar klart" << endl;

	setCurrentWorld(0);
}

void Universe::populateWorlds() 
{
	void PaulInteract(NPC*);
	void ErwinInteract(NPC*);
	void JamesClerkInteract(NPC*);

	void treeInteract(NPC*);
	void SensorseiInteract(World*);

	//OBS!!!!!!
	//UNIKA ID KRÄVS
	addNPC(0, new NPC(1, 100, 10, 0, "Paul", sf::Vector2f(42 * Tile::TILESIZE, 18 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("NPC"), "Here comes the dirac train!", PaulInteract));
	addNPC(1, new NPC(1, 100, 10, 1, "Erwin", sf::Vector2f(10 * Tile::TILESIZE, 5 * Tile::TILESIZE), getWorld(1), gamePointer_->getTexture("NPC"), "Hej, jag heter Erwin!", ErwinInteract));
	addNPC(0, new NPC(1, 100, 10, 2, "James Clerk", sf::Vector2f(10 * Tile::TILESIZE, 3 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("NPC"), "Hej, jag heter James Clerk!", JamesClerkInteract));
	
	addNPC(0, new NPC(1, 100, 10, 3, "Tree", sf::Vector2f(32 * Tile::TILESIZE, 24 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("tree"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 4, "Tree", sf::Vector2f(33 * Tile::TILESIZE, 24 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("tree"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 5, "Tree", sf::Vector2f(34 * Tile::TILESIZE, 24 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("tree"), "", treeInteract));

	addNPC(0, new NPC(1, 100, 10, 6, "Tree", sf::Vector2f(31 * Tile::TILESIZE, 25 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("tree"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 7, "Tree", sf::Vector2f(32 * Tile::TILESIZE, 25 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("tree"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 8, "Tree", sf::Vector2f(33 * Tile::TILESIZE, 25 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("tree"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 9, "Tree", sf::Vector2f(34 * Tile::TILESIZE, 25 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("tree"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 10, "Tree", sf::Vector2f(35 * Tile::TILESIZE, 25 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("tree"), "", treeInteract));

	addNPC(0, new NPC(1, 100, 10, 11, "Tree", sf::Vector2f(30 * Tile::TILESIZE, 26 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("tree"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 12, "Tree", sf::Vector2f(31 * Tile::TILESIZE, 26 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("tree"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 13, "Tree", sf::Vector2f(32 * Tile::TILESIZE, 26 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("tree"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 14, "Tree", sf::Vector2f(33 * Tile::TILESIZE, 26 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("tree"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 15, "Tree", sf::Vector2f(34 * Tile::TILESIZE, 26 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("tree"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 16, "Tree", sf::Vector2f(35 * Tile::TILESIZE, 26 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("tree"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 17, "Tree", sf::Vector2f(36 * Tile::TILESIZE, 26 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("tree"), "", treeInteract));

	addNPC(0, new NPC(1, 100, 10, 18, "Tree", sf::Vector2f(30 * Tile::TILESIZE, 27 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("tree"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 19, "Tree", sf::Vector2f(31 * Tile::TILESIZE, 27 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("tree"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 20, "Tree", sf::Vector2f(32 * Tile::TILESIZE, 27 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("tree"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 21, "Tree", sf::Vector2f(33 * Tile::TILESIZE, 27 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("tree"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 22, "Tree", sf::Vector2f(34 * Tile::TILESIZE, 27* Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("tree"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 23, "Tree", sf::Vector2f(35 * Tile::TILESIZE, 27 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("tree"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 24, "Tree", sf::Vector2f(36 * Tile::TILESIZE, 27 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("tree"), "", treeInteract));

	addNPC(0, new NPC(1, 100, 10, 25, "Tree", sf::Vector2f(31 * Tile::TILESIZE, 28 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("tree"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 26, "Tree", sf::Vector2f(32 * Tile::TILESIZE, 28 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("tree"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 27, "Tree", sf::Vector2f(33 * Tile::TILESIZE, 28 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("tree"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 28, "Tree", sf::Vector2f(34 * Tile::TILESIZE, 28 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("tree"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 29, "Tree", sf::Vector2f(35 * Tile::TILESIZE, 28 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("tree"), "", treeInteract));

	addNPC(0, new NPC(1, 100, 10, 30, "Tree", sf::Vector2f(32 * Tile::TILESIZE, 29 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("tree"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 31, "Tree", sf::Vector2f(33 * Tile::TILESIZE, 29 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("tree"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 32, "Tree", sf::Vector2f(34 * Tile::TILESIZE, 29 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("tree"), "", treeInteract));
	//--------------------------
	addEnemy(0, new Enemy(1, 100, 10, 0, "Pelle", sf::Vector2f(30 * Tile::TILESIZE, 30 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("enemy1")));
	addEnemy(0, new Enemy(1, 100, 10, 1, "Pelle", sf::Vector2f(34 * Tile::TILESIZE, 30 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("enemy2")));
	addEnemy(0, new Enemy(1, 100, 10, 2, "Pelle", sf::Vector2f(36 * Tile::TILESIZE, 30 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("enemy3")));

	addSensor(0, new Sensor(0, "Sensorsei", sf::Vector2f(50 * Tile::TILESIZE, 13 * Tile::TILESIZE), getWorld(1), SensorseiInteract, gamePointer_->getTexture("enemy")));

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

void PaulInteract(NPC* NPCPtr) // TODO Fixa så att han kollar om player har träd i inventory!
{
	NPCPtr->getWorld()->getUniverse()->getGame()->getApp()->getSoundHandler().playSound("diracTrain");

	for (int i = 0; i < 13; ++i)
	{
		NPCPtr->getWorld()->changeTile((13 * NPCPtr->getWorld()->getMapWidth() + 40 + i), 2);
	}
}

void ErwinInteract(NPC* NPCPtr)
{
	NPCPtr->getWorld()->getUniverse()->getGame()->getApp()->setNextFrame(new GameWon(NPCPtr->getWorld()->getUniverse()->getGame()->getApp()));
}

void JamesClerkInteract(NPC* NPCPtr)
{
	NPCPtr->getWorld()->getUniverse()->switchWorld(1, 64, 64);
}

void SensorseiInteract(World* worldPtr)
{
	worldPtr->getUniverse()->switchWorld(1, 64, 64);
}

void treeInteract(NPC* NPCPtr) 
{
	NPCPtr->getWorld()->changeTile(((NPCPtr->getPosition().y/32) * NPCPtr->getWorld()->getMapWidth() + NPCPtr->getPosition().x/32), 9);
	NPCPtr->getWorld()->getUniverse()->getGame()->getPlayer()->getInventory()->addItem(0);
	NPCPtr->die();
}