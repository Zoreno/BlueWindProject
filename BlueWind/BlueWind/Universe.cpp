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
	throw UniverseException("Kunde inte hitta värld med ID:" + ID);
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
	gamePointer_->getApp()->getSoundHandler().playMusic(currentWorld_->getMusic());
}

Tile& Universe::getTile(int i)
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
	tileAtlas_.emplace(1,new Tile(gamePointer_->getTexture("grassTree"), false));
	tileAtlas_.emplace(2, new Tile(gamePointer_->getTexture("bridge"), true));
	tileAtlas_.emplace(3, new Tile(gamePointer_->getTexture("house00"), false));
	tileAtlas_.emplace(4, new Tile(gamePointer_->getTexture("house01"), false));
	tileAtlas_.emplace(5, new Tile(gamePointer_->getTexture("house02"), false));
	tileAtlas_.emplace(6, new Tile(gamePointer_->getTexture("house03"), false));
	tileAtlas_.emplace(7, new Tile(gamePointer_->getTexture("house10"), false));
	tileAtlas_.emplace(8, new Tile(gamePointer_->getTexture("house11"), false));
	tileAtlas_.emplace(9, new Tile(gamePointer_->getTexture("house12"), false));
	tileAtlas_.emplace(10, new Tile(gamePointer_->getTexture("house13"), false));
	tileAtlas_.emplace(11, new Tile(gamePointer_->getTexture("house20"), false));
	tileAtlas_.emplace(12, new Tile(gamePointer_->getTexture("house21"), false));
	tileAtlas_.emplace(13, new Tile(gamePointer_->getTexture("house22"), false));
	tileAtlas_.emplace(14, new Tile(gamePointer_->getTexture("house23"), false));
	tileAtlas_.emplace(15, new Tile(gamePointer_->getTexture("house30"), false));
	tileAtlas_.emplace(16, new Tile(gamePointer_->getTexture("house31"), false));
	tileAtlas_.emplace(17, new Tile(gamePointer_->getTexture("house32"), false));
	tileAtlas_.emplace(18, new Tile(gamePointer_->getTexture("house33"), false));
	tileAtlas_.emplace(19, new Tile(gamePointer_->getTexture("mountainGrass"), false));
	tileAtlas_.emplace(20, new Tile(gamePointer_->getTexture("water"), false));
	tileAtlas_.emplace(21, new Tile(gamePointer_->getTexture("grassStump"), true));
	tileAtlas_.emplace(22, new Tile(gamePointer_->getTexture("snow"), true));
	tileAtlas_.emplace(23, new Tile(gamePointer_->getTexture("snowTree"), false));
	tileAtlas_.emplace(24, new Tile(gamePointer_->getTexture("cactus"), false));
	tileAtlas_.emplace(25, new Tile(gamePointer_->getTexture("sand"), true));
	tileAtlas_.emplace(26, new Tile(gamePointer_->getTexture("palmtree"), false));
	tileAtlas_.emplace(100, new Tile(gamePointer_->getTexture("lava"), false));
	tileAtlas_.emplace(101, new Tile(gamePointer_->getTexture("lavastone"), true));
	tileAtlas_.emplace(102, new Tile(gamePointer_->getTexture("burnedTree"), false));
	
	cout << "Laddning av tiles klart" << endl;
}

void Universe::loadWorlds()
{
	cout << "Laddar in världar" << endl;
	worlds_.push_back(new World(0, this, "res/worlds/world0.bmp", "world0Music"));
	worlds_.push_back(new World(1, this, "res/worlds/world1.bmp", "world1Music"));
	worlds_.push_back(new World(2, this, "res/worlds/world2.bmp", "world2Music"));
	worlds_.push_back(new World(3, this, "res/worlds/world3.bmp", "world3Music"));
	worlds_.push_back(new World(4, this, "res/worlds/world4.bmp", "world4Music"));

	cout << "Laddning av världar klart" << endl;

	setCurrentWorld(0);
}

void Universe::populateWorlds() 
{
	void BridgeGuardInteract(NPC*);
	void CthuluInteract(NPC*);

	void saveGame(NPC*);

	void treeInteract(NPC*);
	void World0_World1Interact(World*);
	void World1_World0Interact(World*);
	void World1_World2Interact(World*);
	void World2_World1Interact(World*);
	void World2_World3Interact(World*);
	void World3_World2Interact(World*);

	void defaultDeath(Enemy*);
	void badAllocDeath(Enemy*);
	void blueWindDeath(Enemy*);
	void isgolathDeath(Enemy*);

	//OBS!!!!!!
	//UNIKA ID KRÄVS

	//-----------------WORLD 0------------------------------------
	//NPC
	addNPC(0, new NPC(1, 100, 10, 0, "Bridge Guard", sf::Vector2f(38 * Tile::TILESIZE, 15 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("NPC"), "", BridgeGuardInteract));
	
	//Träd
	addNPC(0, new NPC(1, 100, 10, 3, "Tree", sf::Vector2f(18 * Tile::TILESIZE, 36 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("grassTreeChoppable"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 4, "Tree", sf::Vector2f(41 * Tile::TILESIZE, 28 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("grassTreeChoppable"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 5, "Tree", sf::Vector2f(37 * Tile::TILESIZE, 31 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("grassTreeChoppable"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 6, "Tree", sf::Vector2f(27 * Tile::TILESIZE, 38 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("grassTreeChoppable"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 7, "Tree", sf::Vector2f(18 * Tile::TILESIZE, 32 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("grassTreeChoppable"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 10, "Tree", sf::Vector2f(47 * Tile::TILESIZE, 36 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("grassTreeChoppable"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 11, "Tree", sf::Vector2f(44 * Tile::TILESIZE, 39 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("grassTreeChoppable"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 12, "Tree", sf::Vector2f(40 * Tile::TILESIZE, 46 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("grassTreeChoppable"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 13, "Tree", sf::Vector2f(30 * Tile::TILESIZE, 47 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("grassTreeChoppable"), "", treeInteract));
	addNPC(0, new NPC(1, 100, 10, 14, "Tree", sf::Vector2f(23 * Tile::TILESIZE, 45 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("grassTreeChoppable"), "", treeInteract));
	
	//Enemies
	addEnemy(0, new Enemy(1, 100, 10, 0, "Pelle", sf::Vector2f(22 * Tile::TILESIZE, 31 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("enemy4"), defaultDeath));
	addEnemy(0, new Enemy(1, 100, 10, 1, "Pelle", sf::Vector2f(30 * Tile::TILESIZE, 42 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("enemy4"), defaultDeath));
	addEnemy(0, new Enemy(1, 100, 10, 2, "Pelle", sf::Vector2f(38 * Tile::TILESIZE, 37 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("enemy4"), defaultDeath));

	//Sensorer
	addSensor(0, new Sensor(0, "World0_World1", sf::Vector2f(66 * Tile::TILESIZE, 13 * Tile::TILESIZE), getWorld(1), World0_World1Interact, gamePointer_->getTexture("enemy")));

	//----------------------------WORLD 1-------------------------
	addSensor(1, new Sensor(0, "World1_World0", sf::Vector2f(12 * Tile::TILESIZE, 14 * Tile::TILESIZE), getWorld(1), World1_World0Interact, gamePointer_->getTexture("enemy")));
	addSensor(1, new Sensor(1, "World1_World2", sf::Vector2f(58 * Tile::TILESIZE, 9 * Tile::TILESIZE), getWorld(1), World1_World2Interact, gamePointer_->getTexture("NPC")));
	addNPC(1, new NPC(1, 100, 10, 0, "Gandalf", sf::Vector2f(49 * Tile::TILESIZE, 35 * Tile::TILESIZE), getWorld(1), gamePointer_->getTexture("saveNPC"), "", saveGame));

	//----------------------------WORLD2--------------------------
	addSensor(2, new Sensor(0, "World2_World1", sf::Vector2f(41* Tile::TILESIZE, 64 * Tile::TILESIZE), getWorld(2), World2_World1Interact, gamePointer_->getTexture("enemy")));
	addSensor(2, new Sensor(1, "World2_World3", sf::Vector2f(70 * Tile::TILESIZE, 17 * Tile::TILESIZE), getWorld(2), World2_World3Interact, gamePointer_->getTexture("enemy")));
	addNPC(2, new NPC(1, 100, 10, 0, "Gandalf", sf::Vector2f(59 * Tile::TILESIZE, 13 * Tile::TILESIZE), getWorld(2), gamePointer_->getTexture("saveNPC"), "", saveGame));

	//Enemy
	addEnemy(2, new Enemy(1, 100, 15, 0, "snowWolf", sf::Vector2f(44 * Tile::TILESIZE, 42 * Tile::TILESIZE), getWorld(2), gamePointer_->getTexture("snowWolf"), defaultDeath));
	addEnemy(2, new Enemy(1, 100, 15, 1, "snowWolf", sf::Vector2f(32 * Tile::TILESIZE, 41 * Tile::TILESIZE), getWorld(2), gamePointer_->getTexture("snowWolf"), defaultDeath));
	addEnemy(2, new Enemy(1, 100, 15, 2, "snowWolf", sf::Vector2f(23 * Tile::TILESIZE, 45 * Tile::TILESIZE), getWorld(2), gamePointer_->getTexture("snowWolf"), defaultDeath));
	addEnemy(2, new Enemy(1, 100, 15, 3, "snowWolf", sf::Vector2f(23 * Tile::TILESIZE, 42 * Tile::TILESIZE), getWorld(2), gamePointer_->getTexture("snowWolf"), defaultDeath));
	addEnemy(2, new Enemy(1, 100, 15, 4, "snowWolf", sf::Vector2f(43 * Tile::TILESIZE, 31 * Tile::TILESIZE), getWorld(2), gamePointer_->getTexture("snowWolf"), defaultDeath));
	addEnemy(2, new Enemy(1, 100, 15, 5, "snowWolf", sf::Vector2f(43 * Tile::TILESIZE, 32 * Tile::TILESIZE), getWorld(2), gamePointer_->getTexture("snowWolf"), defaultDeath));
	addEnemy(2, new Enemy(1, 100, 15, 6, "snowWolf", sf::Vector2f(44 * Tile::TILESIZE, 31 * Tile::TILESIZE), getWorld(2), gamePointer_->getTexture("snowWolf"), defaultDeath));
	addEnemy(2, new Enemy(1, 100, 15, 7, "snowWolf", sf::Vector2f(44 * Tile::TILESIZE, 32 * Tile::TILESIZE), getWorld(2), gamePointer_->getTexture("snowWolf"), defaultDeath));
	addEnemy(2, new Enemy(1, 100, 15, 8, "snowWolf", sf::Vector2f(15 * Tile::TILESIZE, 18 * Tile::TILESIZE), getWorld(2), gamePointer_->getTexture("snowWolf"), defaultDeath));
	addEnemy(2, new Enemy(1, 100, 15, 9, "snowWolf", sf::Vector2f(22 * Tile::TILESIZE, 18 * Tile::TILESIZE), getWorld(2), gamePointer_->getTexture("snowWolf"), defaultDeath));

	addEnemy(2, new Enemy(1, 200, 30, 10, "isgolath", sf::Vector2f(19 * Tile::TILESIZE, 17 * Tile::TILESIZE), getWorld(2), gamePointer_->getTexture("blueWizard"), isgolathDeath));
	//----------------------------WORLD3--------------------------
	addSensor(3, new Sensor(0, "World3_World2", sf::Vector2f(12 * Tile::TILESIZE, 17 * Tile::TILESIZE), getWorld(3), World3_World2Interact, gamePointer_->getTexture("enemy")));
	//NPC
	addNPC(3, new NPC(1, 100, 10, 1, "Cthulu", sf::Vector2f(58 * Tile::TILESIZE, 49 * Tile::TILESIZE), getWorld(3), gamePointer_->getTexture("NPC5"), "I AM CTHULU", CthuluInteract));
	addNPC(3, new NPC(1, 100, 10, 2, "Gandalf", sf::Vector2f(56 * Tile::TILESIZE, 46 * Tile::TILESIZE), getWorld(3), gamePointer_->getTexture("saveNPC"), "", saveGame));

	//----------------------------WORLD4--------------------------
	
	//Enemy
	addEnemy(4, new Enemy(1, 150, 30, 4, "Wizzzard", sf::Vector2f(16 * Tile::TILESIZE, 38 * Tile::TILESIZE), getWorld(4), gamePointer_->getTexture("wizzzard"), defaultDeath));
	addEnemy(4, new Enemy(1, 150, 30, 5, "Wizzzard", sf::Vector2f(24 * Tile::TILESIZE, 43 * Tile::TILESIZE), getWorld(4), gamePointer_->getTexture("wizzzard"), defaultDeath));
	addEnemy(4, new Enemy(1, 150, 30, 6, "Wizzzard", sf::Vector2f(32 * Tile::TILESIZE, 47 * Tile::TILESIZE), getWorld(4), gamePointer_->getTexture("wizzzard"), defaultDeath));
	addEnemy(4, new Enemy(1, 300, 30, 2, "Bad Alloc", sf::Vector2f(46 * Tile::TILESIZE, 49 * Tile::TILESIZE), getWorld(4), gamePointer_->getTexture("badAlloc"), badAllocDeath));
	addEnemy(4, new Enemy(10, 300, 50, 3, "BlueWind", sf::Vector2f(46 * Tile::TILESIZE, 21 * Tile::TILESIZE), getWorld(4), gamePointer_->getTexture("blueWind"), blueWindDeath));
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

void BridgeGuardInteract(NPC* NPCPtr)
{
	UserInterface* UI{ NPCPtr->getWorld()->getUniverse()->getGame()->getUserInterface() };
	int startposition{ 13 * NPCPtr->getWorld()->getMapWidth() + 40 };
	int bridgeLength{ 0 };

	while (NPCPtr->getWorld()->getTileVector().at(startposition) == 2)
	{
		++startposition;
		++bridgeLength;
	}

	while (NPCPtr->getWorld()->getUniverse()->getGame()->getPlayer()->getInventory()->hasItem(0))
	{
		NPCPtr->getWorld()->getUniverse()->getGame()->getPlayer()->getInventory()->removeItem(0);
		NPCPtr->getWorld()->changeTile(startposition, 2);
		++startposition;
		++bridgeLength;
	}

	if (bridgeLength == 0)
	{
		UI->addStringToChatBox("Bring me some wood and I could");
		UI->addStringToChatBox("help you repair the bridge!");
	}

	if (bridgeLength > 0 && bridgeLength < 10)
	{
		UI->addStringToChatBox("I still need some more wood in");
		UI->addStringToChatBox("order to finish the bridge!");
	}

	if (bridgeLength >= 10)
		UI->addStringToChatBox("The bridge is finished!");
	
}


void treeInteract(NPC* NPCPtr) 
{
	if (!NPCPtr->getWorld()->getUniverse()->getGame()->getPlayer()->getInventory()->isFull())
	{
		NPCPtr->getWorld()->changeTile(((NPCPtr->getPosition().y / 32) * NPCPtr->getWorld()->getMapWidth() + NPCPtr->getPosition().x / 32), 21);
		NPCPtr->getWorld()->getUniverse()->getGame()->getPlayer()->getInventory()->addItem(0);
		NPCPtr->die();
	}
	else
	{
		NPCPtr->getWorld()->getUniverse()->getGame()->getUserInterface()->addStringToChatBox("Inventory is full.");
	}
}

void CthuluInteract(NPC* NPCPtr)
{
	NPCPtr->getWorld()->getUniverse()->switchWorld(4, 13 * Tile::TILESIZE, 37 * Tile::TILESIZE);
}

void CthuluInteract2(NPC* NPCPtr)
{
	NPCPtr->getWorld()->getUniverse()->getGame()->getUserInterface()->addStringToChatBox("There is another one!");
	NPCPtr->getWorld()->getUniverse()->switchWorld(4, 12 * Tile::TILESIZE, 15 * Tile::TILESIZE);
}

void World0_World1Interact(World* worldPtr)
{
	worldPtr->getUniverse()->switchWorld(1, 14 * Tile::TILESIZE, 14 * Tile::TILESIZE);
}

void World1_World0Interact(World* worldPtr)
{
	worldPtr->getUniverse()->switchWorld(0, 65 * Tile::TILESIZE, 13 * Tile::TILESIZE);
}

void World1_World2Interact(World* worldPtr)
{
	worldPtr->getUniverse()->switchWorld(2, 41 * Tile::TILESIZE, 63 * Tile::TILESIZE);
}

void World2_World1Interact(World* worldPtr)
{
	worldPtr->getUniverse()->switchWorld(1, 58 * Tile::TILESIZE, 10 * Tile::TILESIZE);
}

void World2_World3Interact(World* worldPtr)
{
	worldPtr->getUniverse()->switchWorld(3, 13 * Tile::TILESIZE, 17 * Tile::TILESIZE);
}

void World3_World2Interact(World* worldPtr)
{
	worldPtr->getUniverse()->switchWorld(2, 69 * Tile::TILESIZE, 17 * Tile::TILESIZE);
}

void defaultDeath(Enemy* enemyPtr)
{
	cout << "Enemy died!" << endl;
	enemyPtr->getWorld()->getUniverse()->getGame()->getPlayer()->addExperience(20);
	enemyPtr->getWorld()->removeEnemy(enemyPtr);
}

void isgolathDeath(Enemy* enemyPtr)
{
	UserInterface* UI{ enemyPtr->getWorld()->getUniverse()->getGame()->getUserInterface() };
	UI->addStringToChatBox("Oh no, you defeated me!");
	UI->addStringToChatBox("Bluewind will revenge me!");
	cout << "Enemy died!" << endl;
	enemyPtr->getWorld()->getUniverse()->getGame()->getPlayer()->addExperience(50);
	enemyPtr->getWorld()->removeEnemy(enemyPtr);
}


void badAllocDeath(Enemy* enemyPtr)
{
	enemyPtr->getWorld()->getUniverse()->getGame()->getPlayer()->addExperience(2000);
	enemyPtr->getWorld()->removeEnemy(enemyPtr);
	cout << "Bad-Alloc is dead!" << endl;
	enemyPtr->getWorld()->getUniverse()->addNPC(4, new NPC(1, 100, 10, 3, "Cthulu", sf::Vector2f(46 * Tile::TILESIZE, 49 * Tile::TILESIZE), enemyPtr->getWorld()->getUniverse()->getWorld(4), enemyPtr->getWorld()->getUniverse()->getGame()->getTexture("NPC5"), "I AM CTHULU", CthuluInteract2));
}

void blueWindDeath(Enemy* enemyPtr)
{
	enemyPtr->getWorld()->removeEnemy(enemyPtr);
	Application* AppPtr{ enemyPtr->getWorld()->getUniverse()->getGame()->getApp() };
	AppPtr->setNextFrame(new GameWon(AppPtr));
}

void saveGame(NPC* NPCPtr)
{
	NPCPtr->getWorld()->getUniverse()->getGame()->saveGame();
	NPCPtr->getWorld()->getUniverse()->getGame()->getUserInterface()->addStringToChatBox("Game saved!");
}
