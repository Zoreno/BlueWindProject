#include "Universe.h"
#include "Game.h"
#include "World.h" 
#include "Tile.h"
#include "Application.h"
#include "GameWon.h"
#include "NPC.h"
#include <iostream>
#include "Inventory.h"

using namespace std;

Universe::Universe(Game * gamePtr)
	: gamePointer_{ gamePtr }
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
	tileAtlas_.emplace(0, new Tile(gamePointer_->getTexture("grass"), true));
	tileAtlas_.emplace(1, new Tile(gamePointer_->getTexture("grassTree"), false));
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
	tileAtlas_.emplace(200, new Tile(gamePointer_->getTexture("fountain"), false));
	tileAtlas_.emplace(201, new Tile(gamePointer_->getTexture("noneWalkableSand"), false));
	tileAtlas_.emplace(900, new Tile(gamePointer_->getTexture("grassBurnedTree"), false));
	tileAtlas_.emplace(901, new Tile(gamePointer_->getTexture("burnedGround"), false));
	tileAtlas_.emplace(902, new Tile(gamePointer_->getTexture("grassStone"), false));
	
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
	worlds_.push_back(new World(5, this, "res/worlds/world5.bmp", "world1Music"));

	cout << "Laddning av världar klart" << endl;

	setCurrentWorld(0);
}

void Universe::populateCity()
{
	void citizenInteract(NPC*);
	void saveGame(NPC*);
	void thankfulManInteract(NPC*);
	void thankfulCitizen(NPC*);

	addNPC(1, new NPC(1, 100, 10, 0, "Gandalf", sf::Vector2f(35 * Tile::TILESIZE, 21 * Tile::TILESIZE), getWorld(1), gamePointer_->getTexture("citizenMan1"), "", citizenInteract));
	addNPC(1, new NPC(1, 100, 10, 1, "Citizen", sf::Vector2f(54 * Tile::TILESIZE, 21 * Tile::TILESIZE), getWorld(1), gamePointer_->getTexture("citizenMan2"), "", citizenInteract));
	addNPC(1, new NPC(1, 100, 10, 2, "Citizen", sf::Vector2f(44 * Tile::TILESIZE, 36 * Tile::TILESIZE), getWorld(1), gamePointer_->getTexture("cityPriest"), "", citizenInteract));
	addNPC(1, new NPC(1, 100, 10, 3, "Citizen", sf::Vector2f(64 * Tile::TILESIZE, 39 * Tile::TILESIZE), getWorld(1), gamePointer_->getTexture("citizenWoman2"), "", citizenInteract));
	addNPC(1, new NPC(1, 100, 10, 4, "Citizen", sf::Vector2f(48 * Tile::TILESIZE, 21 * Tile::TILESIZE), getWorld(1), gamePointer_->getTexture("bridgeguard"), "", citizenInteract));
	addNPC(1, new NPC(1, 100, 10, 5, "Citizen", sf::Vector2f(36 * Tile::TILESIZE, 47 * Tile::TILESIZE), getWorld(1), gamePointer_->getTexture("warrior"), "", citizenInteract));
	addNPC(1, new NPC(1, 100, 10, 6, "Citizen", sf::Vector2f(31 * Tile::TILESIZE, 30 * Tile::TILESIZE), getWorld(1), gamePointer_->getTexture("citizenWoman1"), "", citizenInteract));
	addNPC(1, new NPC(1, 100, 10, 7, "Citizen", sf::Vector2f(29 * Tile::TILESIZE, 45 * Tile::TILESIZE), getWorld(1), gamePointer_->getTexture("citizenBoy1"), "", citizenInteract));
	addNPC(1, new NPC(1, 100, 10, 8, "Citizen", sf::Vector2f(54 * Tile::TILESIZE, 27 * Tile::TILESIZE), getWorld(1), gamePointer_->getTexture("citizenGirl1"), "*Thank you for saving us!", thankfulManInteract));
	addNPC(1, new NPC(1, 100, 10, 9, "Gandalf", sf::Vector2f(49 * Tile::TILESIZE, 33 * Tile::TILESIZE), getWorld(1), gamePointer_->getTexture("saveNPC"), "", saveGame));
	addNPC(1, new NPC(1, 100, 10, 10, "Simon", sf::Vector2f(41 * Tile::TILESIZE, 42 * Tile::TILESIZE), getWorld(1), gamePointer_->getTexture("citizenWoman3"), "T*hank you for saving us!", thankfulCitizen));
}

void Universe::populateWorlds() 
{
	void BridgeGuardInteract(NPC*);
	void CthuluInteract(NPC*);
	void GirlInteract(NPC*);
	void citizenInteract(NPC*);
	void energyPowerupInteract(NPC*);
	void snowChestInteract(NPC*);
	void world5GuyInteract(NPC*);
	void FirimaniumsInteract(NPC*);
	void manInValleyInteract(NPC*);

	void saveGame(NPC*);

	void treeInteract(NPC*);
	void stoneInteract(NPC*);

	void World0_World1Interact(World*);
	void World1_World0Interact(World*);
	void World1_World2Interact(World*);
	void World2_World1Interact(World*);
	void World2_World3Interact(World*);
	void World3_World2Interact(World*);
	void World1_World5Interact(World*);
	void World5_World1Interact(World*);
	void houseFireInteract(World*);
	void brokenFountainInteract1(NPC*);
	void brokenFountainInteract2(NPC*);
	void brokenFountainInteract3(NPC*);
	void brokenFountainInteract4(NPC*);

	void defaultDeath(Enemy*);
	void badAllocDeath(Enemy*);
	void blueWindDeath(Enemy*);
	void isgolathDeath(Enemy*);
	void minotaurDeath(Enemy*);
	void fireDeath(Enemy*); //
	void superGhostDeath(Enemy*);

	void voidFkn(NPC*);

	//OBS!!!!!!
	//UNIKA ID KRÄVS

	//-----------------WORLD 0------------------------------------
	//NPC
	addNPC(0, new NPC(1, 100, 10, 0, "bridge guard", sf::Vector2f(38 * Tile::TILESIZE, 15 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("bridgeguard"), "", BridgeGuardInteract));
	addNPC(0, new NPC(1, 100, 10, 1, "first one", sf::Vector2f(20 * Tile::TILESIZE, 16 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("citizenWoman1"), "", GirlInteract));
	addNPC(0, new NPC(1, 100, 10, 2, "ringgiver", sf::Vector2f(39 * Tile::TILESIZE, 12 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("citizenWoman2"), "", energyPowerupInteract));

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
	addEnemy(0, new Enemy(1, 100, 10, 0, "demon1", sf::Vector2f(22 * Tile::TILESIZE, 31 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("demon"), defaultDeath));
	addEnemy(0, new Enemy(1, 100, 10, 1, "demon2", sf::Vector2f(30 * Tile::TILESIZE, 42 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("demon"), defaultDeath));
	addEnemy(0, new Enemy(1, 100, 10, 2, "demon3", sf::Vector2f(38 * Tile::TILESIZE, 37 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("demon"), defaultDeath));
	addEnemy(0, new Enemy(1, 100, 10, 3, "demon4", sf::Vector2f(27 * Tile::TILESIZE, 23 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("demon"), defaultDeath));
	addEnemy(0, new Enemy(1, 0, 40000, 4, "you die", sf::Vector2f(48 * Tile::TILESIZE, 22 * Tile::TILESIZE), getWorld(0), gamePointer_->getTexture("yourEx"), fireDeath));

	//Sensorer
	addSensor(0, new Sensor(0, "World0_World1", sf::Vector2f(66 * Tile::TILESIZE, 13 * Tile::TILESIZE), getWorld(1), World0_World1Interact, gamePointer_->getTexture("void")));

	//----------------------------WORLD 1-------------------------
	//NPC
	addNPC(1, new NPC(1, 100, 10, 11, "Stone", sf::Vector2f(58 * Tile::TILESIZE, 12 * Tile::TILESIZE), getWorld(1), gamePointer_->getTexture("grassStone"), "", stoneInteract));
	addNPC(1, new NPC(1, 100, 10, 12, "Citizen1", sf::Vector2f(29 * Tile::TILESIZE, 13 * Tile::TILESIZE), getWorld(1), gamePointer_->getTexture("citizenBoy1"), "*Please save us from the minotaur!", voidFkn));
	addNPC(1, new NPC(1, 100, 10, 13, "Citizen2", sf::Vector2f(54 * Tile::TILESIZE, 50 * Tile::TILESIZE), getWorld(5), gamePointer_->getTexture("citizenGirl2"), "*This is where the wizard lives", voidFkn));

	//Enemies
	addEnemy(1, new Enemy(1, 150, 20, 2, "Minotaur", sf::Vector2f(36 * Tile::TILESIZE, 32 * Tile::TILESIZE), getWorld(1), gamePointer_->getTexture("minotaur"), minotaurDeath));
	
	//Sensor
	addSensor(1, new Sensor(0, "World1_World0", sf::Vector2f(12 * Tile::TILESIZE, 14 * Tile::TILESIZE), getWorld(1), World1_World0Interact, gamePointer_->getTexture("void")));
	addSensor(1, new Sensor(1, "World1_World2", sf::Vector2f(58 * Tile::TILESIZE, 9 * Tile::TILESIZE), getWorld(1), World1_World2Interact, gamePointer_->getTexture("void")));
	addSensor(1, new Sensor(2, "World1_World5", sf::Vector2f(56 * Tile::TILESIZE, 54 * Tile::TILESIZE), getWorld(1), World1_World5Interact, gamePointer_->getTexture("void")));

	//----------------------------WORLD2--------------------------
	// NPC
	addNPC(2, new NPC(1, 100, 10, 0, "Gandalf", sf::Vector2f(55 * Tile::TILESIZE, 12 * Tile::TILESIZE), getWorld(2), gamePointer_->getTexture("saveNPC"), "", saveGame));
	addNPC(2, new NPC(1, 100, 10, 1, "Chest", sf::Vector2f(19 * Tile::TILESIZE, 9 * Tile::TILESIZE), getWorld(2), gamePointer_->getTexture("snowChest"), "", snowChestInteract));
	addNPC(2, new NPC(1, 100, 10, 2, "valleyman", sf::Vector2f(39 * Tile::TILESIZE, 49 * Tile::TILESIZE), getWorld(2), gamePointer_->getTexture("warrior"), "", manInValleyInteract));

	//Enemies
	addEnemy(2, new Enemy(1, 350, 30, 0, "snowWolf1", sf::Vector2f(44 * Tile::TILESIZE, 42 * Tile::TILESIZE), getWorld(2), gamePointer_->getTexture("snowWolf"), defaultDeath));
	addEnemy(2, new Enemy(1, 350, 30, 1, "snowWolf2", sf::Vector2f(32 * Tile::TILESIZE, 41 * Tile::TILESIZE), getWorld(2), gamePointer_->getTexture("snowWolf"), defaultDeath));
	addEnemy(2, new Enemy(1, 350, 30, 2, "snowWolf3", sf::Vector2f(23 * Tile::TILESIZE, 45 * Tile::TILESIZE), getWorld(2), gamePointer_->getTexture("snowWolf"), defaultDeath));
	addEnemy(2, new Enemy(1, 400, 30, 3, "snowWolf4", sf::Vector2f(23 * Tile::TILESIZE, 42 * Tile::TILESIZE), getWorld(2), gamePointer_->getTexture("snowWolf"), defaultDeath));
	addEnemy(2, new Enemy(1, 400, 30, 4, "snowWolf5", sf::Vector2f(43 * Tile::TILESIZE, 31 * Tile::TILESIZE), getWorld(2), gamePointer_->getTexture("snowWolf"), defaultDeath));
	addEnemy(2, new Enemy(1, 400, 30, 5, "snowWolf6", sf::Vector2f(43 * Tile::TILESIZE, 32 * Tile::TILESIZE), getWorld(2), gamePointer_->getTexture("snowWolf"), defaultDeath));
	addEnemy(2, new Enemy(1, 400, 30, 6, "snowWolf7", sf::Vector2f(44 * Tile::TILESIZE, 31 * Tile::TILESIZE), getWorld(2), gamePointer_->getTexture("snowWolf"), defaultDeath));
	addEnemy(2, new Enemy(1, 400, 30, 7, "snowWolf8", sf::Vector2f(44 * Tile::TILESIZE, 32 * Tile::TILESIZE), getWorld(2), gamePointer_->getTexture("snowWolf"), defaultDeath));
	addEnemy(2, new Enemy(1, 450, 40, 8, "snowWolf9", sf::Vector2f(15 * Tile::TILESIZE, 18 * Tile::TILESIZE), getWorld(2), gamePointer_->getTexture("snowWolf"), defaultDeath));
	addEnemy(2, new Enemy(1, 450, 40, 9, "snowWolf10", sf::Vector2f(22 * Tile::TILESIZE, 18 * Tile::TILESIZE), getWorld(2), gamePointer_->getTexture("snowWolf"), defaultDeath));
	addEnemy(2, new Enemy(1, 650, 30, 10, "Isgolath", sf::Vector2f(19 * Tile::TILESIZE, 17 * Tile::TILESIZE), getWorld(2), gamePointer_->getTexture("blueWizard"), isgolathDeath));

	//Sensor
	addSensor(2, new Sensor(0, "World2_World1", sf::Vector2f(41 * Tile::TILESIZE, 64 * Tile::TILESIZE), getWorld(2), World2_World1Interact, gamePointer_->getTexture("void")));
	addSensor(2, new Sensor(1, "World2_World3", sf::Vector2f(70 * Tile::TILESIZE, 17 * Tile::TILESIZE), getWorld(2), World2_World3Interact, gamePointer_->getTexture("void")));

	//----------------------------WORLD3--------------------------
	//NPC
	addNPC(3, new NPC(1, 100, 10, 1, "Cthulu", sf::Vector2f(38 * Tile::TILESIZE, 34 * Tile::TILESIZE), getWorld(3), gamePointer_->getTexture("NPC5"), "*I AM CTHULU!", CthuluInteract));

	addNPC(3, new NPC(1, 100, 10, 3, "Broken Fountain1", sf::Vector2f(33 * Tile::TILESIZE, 23 * Tile::TILESIZE), getWorld(3), gamePointer_->getTexture("brokenFountain"), "", brokenFountainInteract1));
	addNPC(3, new NPC(1, 100, 10, 4, "Broken Fountain2", sf::Vector2f(43 * Tile::TILESIZE, 23 * Tile::TILESIZE), getWorld(3), gamePointer_->getTexture("brokenFountain"), "", brokenFountainInteract2));
	addNPC(3, new NPC(1, 100, 10, 5, "Broken Fountain3", sf::Vector2f(33 * Tile::TILESIZE, 33 * Tile::TILESIZE), getWorld(3), gamePointer_->getTexture("brokenFountain"), "", brokenFountainInteract3));
	addNPC(3, new NPC(1, 100, 10, 6, "Broken Fountain4", sf::Vector2f(43 * Tile::TILESIZE, 33 * Tile::TILESIZE), getWorld(3), gamePointer_->getTexture("brokenFountain"), "", brokenFountainInteract4));


	//Enemy
	addEnemy(3, new Enemy(1, 1000, 25, 0, "ghost", sf::Vector2f(32 * Tile::TILESIZE, 16 * Tile::TILESIZE), getWorld(3), gamePointer_->getTexture("ghost"), defaultDeath));
	addEnemy(3, new Enemy(1, 1000, 25, 1, "ghost", sf::Vector2f(25 * Tile::TILESIZE, 24 * Tile::TILESIZE), getWorld(3), gamePointer_->getTexture("ghost"), defaultDeath));
	addEnemy(3, new Enemy(1, 1000, 25, 2, "ghost", sf::Vector2f(52 * Tile::TILESIZE, 20 * Tile::TILESIZE), getWorld(3), gamePointer_->getTexture("ghost"), defaultDeath));
	addEnemy(3, new Enemy(1, 1000, 25, 3, "ghost", sf::Vector2f(31 * Tile::TILESIZE, 44 * Tile::TILESIZE), getWorld(3), gamePointer_->getTexture("ghost"), defaultDeath));
	addEnemy(3, new Enemy(1, 1000, 25, 4, "ghost", sf::Vector2f(32 * Tile::TILESIZE, 44 * Tile::TILESIZE), getWorld(3), gamePointer_->getTexture("ghost"), defaultDeath));
	addEnemy(3, new Enemy(1, 1000, 25, 5, "ghost", sf::Vector2f(46 * Tile::TILESIZE, 39 * Tile::TILESIZE), getWorld(3), gamePointer_->getTexture("ghost"), defaultDeath));
	addEnemy(3, new Enemy(1, 1000, 25, 6, "ghost", sf::Vector2f(47 * Tile::TILESIZE, 39 * Tile::TILESIZE), getWorld(3), gamePointer_->getTexture("ghost"), defaultDeath));
	addEnemy(3, new Enemy(1, 1000, 25, 7, "ghost", sf::Vector2f(46 * Tile::TILESIZE, 40 * Tile::TILESIZE), getWorld(3), gamePointer_->getTexture("ghost"), defaultDeath));
	addEnemy(3, new Enemy(1, 1000, 25, 8, "ghost", sf::Vector2f(47 * Tile::TILESIZE, 40 * Tile::TILESIZE), getWorld(3), gamePointer_->getTexture("ghost"), defaultDeath));

	addEnemy(3, new Enemy(1, 1000, 30, 9, "superGhost1", sf::Vector2f(37 * Tile::TILESIZE, 27 * Tile::TILESIZE), getWorld(3), gamePointer_->getTexture("ghost"), superGhostDeath));

	// Sensor
	addSensor(3, new Sensor(0, "World3_World2", sf::Vector2f(12 * Tile::TILESIZE, 17 * Tile::TILESIZE), getWorld(3), World3_World2Interact, gamePointer_->getTexture("void")));

	//----------------------------WORLD4--------------------------
	
	//NPC
	addNPC(4, new NPC(1, 100, 10, 2, "Gandalf", sf::Vector2f(13 * Tile::TILESIZE, 41 * Tile::TILESIZE), getWorld(4), gamePointer_->getTexture("saveNPC"), "", saveGame));

	//Enemy
	addEnemy(4, new Enemy(1, 1500, 50, 4, "redWizard", sf::Vector2f(16 * Tile::TILESIZE, 38 * Tile::TILESIZE), getWorld(4), gamePointer_->getTexture("redWizard"), defaultDeath));
	addEnemy(4, new Enemy(1, 1500, 50, 5, "redWizard", sf::Vector2f(24 * Tile::TILESIZE, 43 * Tile::TILESIZE), getWorld(4), gamePointer_->getTexture("redWizard"), defaultDeath));
	addEnemy(4, new Enemy(1, 1500, 50, 6, "redWizard", sf::Vector2f(32 * Tile::TILESIZE, 47 * Tile::TILESIZE), getWorld(4), gamePointer_->getTexture("redWizard"), defaultDeath));
	addEnemy(4, new Enemy(1, 2800, 30, 2, "Bad Alloc", sf::Vector2f(46 * Tile::TILESIZE, 49 * Tile::TILESIZE), getWorld(4), gamePointer_->getTexture("badAlloc"), badAllocDeath));
	addEnemy(4, new Enemy(10, 7000, 70, 3, "BlueWind", sf::Vector2f(49 * Tile::TILESIZE, 22 * Tile::TILESIZE), getWorld(4), gamePointer_->getTexture("blueWind"), blueWindDeath));

    //------------------------WORLD5-----------------------------
	// NPC
	addNPC(5, new NPC(1, 100, 10, 0, "Guy", sf::Vector2f(25 * Tile::TILESIZE, 48 * Tile::TILESIZE), getWorld(5), gamePointer_->getTexture("citizenWoman1"), "", world5GuyInteract));
	addNPC(5, new NPC(1, 100, 10, 1, "Firimaniums", sf::Vector2f(18 * Tile::TILESIZE, 32 * Tile::TILESIZE), getWorld(5), gamePointer_->getTexture("Firimaniums"), "", FirimaniumsInteract));
	addNPC(5, new NPC(1, 100, 10, 2, "CitizenInWorld1", sf::Vector2f(29 * Tile::TILESIZE, 10 * Tile::TILESIZE), getWorld(5), gamePointer_->getTexture("citizenGirl2"), "", voidFkn));

	// Enemies
	addEnemy(5, new Enemy(1, 200, 20, 0, "demon1", sf::Vector2f(30 * Tile::TILESIZE, 33 * Tile::TILESIZE), getWorld(5), gamePointer_->getTexture("demon"), defaultDeath));
	addEnemy(5, new Enemy(1, 200, 20, 1, "demon2", sf::Vector2f(30 * Tile::TILESIZE, 44 * Tile::TILESIZE), getWorld(5), gamePointer_->getTexture("demon"), defaultDeath));
	addEnemy(5, new Enemy(1, 200, 20, 2, "demon3", sf::Vector2f(29 * Tile::TILESIZE, 52 * Tile::TILESIZE), getWorld(5), gamePointer_->getTexture("demon"), defaultDeath));
	addEnemy(5, new Enemy(1, 200, 20, 3, "demon4", sf::Vector2f(20 * Tile::TILESIZE, 48 * Tile::TILESIZE), getWorld(5), gamePointer_->getTexture("demon"), defaultDeath));
	addEnemy(5, new Enemy(1, 200, 20, 4, "demon5", sf::Vector2f(25 * Tile::TILESIZE, 39 * Tile::TILESIZE), getWorld(5), gamePointer_->getTexture("demon"), defaultDeath));

	// Sensor
	addSensor(5, new Sensor(0, "World5_World1", sf::Vector2f(31 * Tile::TILESIZE, 12 * Tile::TILESIZE), getWorld(5), World5_World1Interact, gamePointer_->getTexture("void")));
	addSensor(5, new Sensor(1, "houseFireSensor", sf::Vector2f(20 * Tile::TILESIZE, 29 * Tile::TILESIZE), getWorld(5), houseFireInteract, gamePointer_->getTexture("void")));

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

	if (!NPCPtr->getWorld()->getUniverse()->getGame()->getGameState()->bridge1Built)
	{
		while (NPCPtr->getWorld()->getTileVector().at(startposition) == 2)
		{
			++startposition;
			++bridgeLength;
		}

		while (NPCPtr->getWorld()->getUniverse()->getGame()->getPlayer()->getInventory()->hasItem(0) && bridgeLength < 10)
		{
			NPCPtr->getWorld()->getUniverse()->getGame()->getPlayer()->getInventory()->removeItem(0);
			NPCPtr->getWorld()->changeTile(startposition, 2);
			++startposition;
			++bridgeLength;
		}

		if (bridgeLength == 0)
		{
			UI->addStringToChatBox("*Bring me some wood and I can");
			UI->addStringToChatBox("help you repair the bridge!");
			return;
		}

		if (bridgeLength > 0 && bridgeLength < 10)
		{
			UI->addStringToChatBox("*I still need some more wood in");
			UI->addStringToChatBox("order to finish the bridge!");
			return;
		}

		if (bridgeLength >= 10)
		{
			NPCPtr->getWorld()->getUniverse()->getGame()->getGameState()->bridge1Built = true;
		}

	}
	UI->addStringToChatBox("*The bridge is finished! You may");
	UI->addStringToChatBox("proceed to the town.");
	
}

void voidFkn(NPC*)
{
}

void treeInteract(NPC* NPCPtr) 
{
	if (!NPCPtr->getWorld()->getUniverse()->getGame()->getPlayer()->getInventory()->isFull())
	{
		NPCPtr->getWorld()->changeTile(((static_cast<int>(NPCPtr->getPosition().y) / 32) * NPCPtr->getWorld()->getMapWidth() + static_cast<int>(NPCPtr->getPosition().x) / 32), 21);
		NPCPtr->getWorld()->getUniverse()->getGame()->getPlayer()->getInventory()->addItem(0);
		NPCPtr->getWorld()->getUniverse()->getGame()->getApp()->getSoundHandler().playSound("itemAdded");
		NPCPtr->die();
	}
	else
	{
		NPCPtr->getWorld()->getUniverse()->getGame()->getUserInterface()->addStringToChatBox("*Inventory is full.");
	}
}

void stoneInteract(NPC* NPCPtr)
{
	if (NPCPtr->getWorld()->getUniverse()->getGame()->getPlayer()->getInventory()->hasItem(1))
	{
		NPCPtr->die();
		int startposition{ 12 * NPCPtr->getWorld()->getMapWidth() + 58 };
		NPCPtr->getWorld()->changeTile(startposition, 0);
		startposition = 65 * NPCPtr->getWorld()->getUniverse()->getWorld(2)->getMapWidth() + 41;
		NPCPtr->getWorld()->getUniverse()->getWorld(2)->changeTile(startposition, 0);
	}
}

void CthuluInteract(NPC* NPCPtr)
{
	if ((NPCPtr->getWorld()->getTileVector().at(23 * NPCPtr->getWorld()->getMapWidth() + 33) == 200)&&
		(NPCPtr->getWorld()->getTileVector().at(23 * NPCPtr->getWorld()->getMapWidth() + 43) == 200)&&
		(NPCPtr->getWorld()->getTileVector().at(33 * NPCPtr->getWorld()->getMapWidth() + 33) == 200)&&
		(NPCPtr->getWorld()->getTileVector().at(33 * NPCPtr->getWorld()->getMapWidth() + 43) == 200))
	{
			
		UserInterface* UI{ NPCPtr->getWorld()->getUniverse()->getGame()->getUserInterface() };
		UI->addStringToChatBox("*Well done! You have repaired my");
		UI->addStringToChatBox("fabulous fountains, many thanks.");
		UI->addStringToChatBox("Good luck almighty, potent,");
		UI->addStringToChatBox("invincible, awesome Faranos!");
	NPCPtr->getWorld()->getUniverse()->switchWorld(4, 13 * Tile::TILESIZE, 37 * Tile::TILESIZE);
	
	}
	else
	{
		UserInterface* UI{ NPCPtr->getWorld()->getUniverse()->getGame()->getUserInterface() };
		UI->addStringToChatBox("*Greetings Faranos! I can teleport you");
		UI->addStringToChatBox("to the dreadful realm of Bad Alloc,");
		UI->addStringToChatBox("but I need the power of my four magic");
		UI->addStringToChatBox("fountains. Repair them for me!");
	}
}

void citizenInteract(NPC* NPCPtr)
{
	NPCPtr->getWorld()->getUniverse()->getGame()->getUserInterface()->addStringToChatBox("*Thank you for saving us!");
}

void GirlInteract(NPC* NPCPtr)
{
	UserInterface* UI{ NPCPtr->getWorld()->getUniverse()->getGame()->getUserInterface() };	
	UI->addStringToChatBox("*Faranos? Thank god you are here!");
	UI->addStringToChatBox("You must defeat Bad Alloc, his dark");
	UI->addStringToChatBox("minions are destroying the"); 
	UI->addStringToChatBox("beautiful land of MaroWind!");
}

void manInValleyInteract(NPC* NPCPtr)
{
	UserInterface* UI{ NPCPtr->getWorld()->getUniverse()->getGame()->getUserInterface() };
	UI->addStringToChatBox("*The bridge on the other side of the");
	UI->addStringToChatBox("valley has been destroyed. Clear the");
	UI->addStringToChatBox("mountain pass of Bad Allocs minions");
	UI->addStringToChatBox("for us and we shall fix it!");
}

void CthuluInteract2(NPC* NPCPtr)
{
	NPCPtr->getWorld()->getUniverse()->getGame()->getUserInterface()->addStringToChatBox("*There is another one!");
	NPCPtr->getWorld()->getUniverse()->switchWorld(4, 14 * Tile::TILESIZE, 15 * Tile::TILESIZE);
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

void World1_World5Interact(World* worldPtr)
{
	worldPtr->getUniverse()->switchWorld(5, 31 * Tile::TILESIZE, 13 * Tile::TILESIZE);
}

void World5_World1Interact(World* worldPtr)
{
	worldPtr->getUniverse()->switchWorld(1, 56 * Tile::TILESIZE, 53 * Tile::TILESIZE);
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

void saveGame(NPC* NPCPtr)
{
	NPCPtr->getWorld()->getUniverse()->getGame()->saveGame();
	NPCPtr->getWorld()->getUniverse()->getGame()->getUserInterface()->addStringToChatBox("*Game saved!");
}

void thankfulManInteract(NPC* NPCPtr)
{
	Inventory* inv{ NPCPtr->getWorld()->getUniverse()->getGame()->getPlayer()->getInventory() };
	if (!inv->isFull() && !inv->hasItem(1))
	{
		NPCPtr->getWorld()->getUniverse()->getGame()->getUserInterface()->addStringToChatBox("*I give you my pickaxe! It might");
		NPCPtr->getWorld()->getUniverse()->getGame()->getUserInterface()->addStringToChatBox("come in handy on your journey.");
		NPCPtr->getWorld()->getUniverse()->getGame()->getPlayer()->getInventory()->addItem(1);
		NPCPtr->getWorld()->getUniverse()->getGame()->getApp()->getSoundHandler().playSound("itemAdded");
	}
}

void thankfulCitizen(NPC* NPCPtr)
{
	UserInterface* UI{ NPCPtr->getWorld()->getUniverse()->getGame()->getUserInterface() };
	Inventory* inv{ NPCPtr->getWorld()->getUniverse()->getGame()->getPlayer()->getInventory() };
		
	if (!inv->isFull() && !inv->hasItem(3))
		{
			UI->addStringToChatBox("*Take this armour as protection");
			UI->addStringToChatBox("from Bad Allocs servants!");
			inv->addItem(3);
			NPCPtr->getWorld()->getUniverse()->getGame()->getApp()->getSoundHandler().playSound("itemAdded");
			Player* player{ NPCPtr->getWorld()->getUniverse()->getGame()->getPlayer() };
			player->setMaxHealth(player->getMaxHealth() + 10);
		}
}

void minotaurDeath(Enemy* enemyPtr)
{
	enemyPtr->getWorld()->getUniverse()->getGame()->getPlayer()->addExperience(70);

	if (!enemyPtr->getWorld()->getUniverse()->getGame()->getGameState()->minotaurDead)
	{
		enemyPtr->getWorld()->getUniverse()->getGame()->getGameState()->minotaurDead = true;
		enemyPtr->getWorld()->getUniverse()->populateCity();
	}
	enemyPtr->getWorld()->removeEnemy(enemyPtr);
}

void isgolathDeath(Enemy* enemyPtr)
{
	UserInterface* UI{ enemyPtr->getWorld()->getUniverse()->getGame()->getUserInterface() };
	UI->addStringToChatBox("*Oh no, I have been defeated!");
	UI->addStringToChatBox("Bluewind will avenge me!");

	if (!enemyPtr->getWorld()->getUniverse()->getGame()->getGameState()->bridge2Built)
	{
		int startposition{ 17 * enemyPtr->getWorld()->getMapWidth() + 63 };

		for (int i{ 0 }; i < 2; ++i)
		{
			enemyPtr->getWorld()->changeTile(startposition + i, 2);
		}

		enemyPtr->getWorld()->getUniverse()->getGame()->getGameState()->bridge2Built = true;
	}

	enemyPtr->getWorld()->getUniverse()->getGame()->getPlayer()->addExperience(50);
	enemyPtr->getWorld()->removeEnemy(enemyPtr);
}


void badAllocDeath(Enemy* enemyPtr)
{
	enemyPtr->getWorld()->getUniverse()->getGame()->getPlayer()->addExperience(2000);
	enemyPtr->getWorld()->removeEnemy(enemyPtr);
	cout << "Bad Alloc is dead!" << endl;
	enemyPtr->getWorld()->getUniverse()->addNPC(4, new NPC(1, 100, 10, 3, "Cthulu", sf::Vector2f(46 * Tile::TILESIZE, 49 * Tile::TILESIZE), enemyPtr->getWorld()->getUniverse()->getWorld(4), enemyPtr->getWorld()->getUniverse()->getGame()->getTexture("NPC5"), "*I AM CTHULU", CthuluInteract2));
}

void blueWindDeath(Enemy* enemyPtr)
{
	enemyPtr->getWorld()->removeEnemy(enemyPtr);
	Application* AppPtr{ enemyPtr->getWorld()->getUniverse()->getGame()->getApp() };
	AppPtr->setNextFrame(new GameWon(AppPtr));
}

void fireDeath(Enemy* enemyPtr)
{
}

void energyPowerupInteract(NPC* NPCPtr)
{
	UserInterface* UI{ NPCPtr->getWorld()->getUniverse()->getGame()->getUserInterface() };
	if (NPCPtr->getWorld()->getTileVector().at(13 * NPCPtr->getWorld()->getMapWidth() + 49) == 2)
	{
		UI->addStringToChatBox("*Thanks for repairing the bridge.");
		UI->addStringToChatBox("Take my magic ring as a token of");
		UI->addStringToChatBox("my gratitude.");

		Inventory* inv{ NPCPtr->getWorld()->getUniverse()->getGame()->getPlayer()->getInventory() };
		if (!inv->isFull() && !inv->hasItem(2))
		{
			inv->addItem(2);
			NPCPtr->getWorld()->getUniverse()->getGame()->getApp()->getSoundHandler().playSound("itemAdded");
			Player* player{ NPCPtr->getWorld()->getUniverse()->getGame()->getPlayer() };
			player->setMaxMana(player->getMana() + 10);
		}
	}
	else
	{
		UI->addStringToChatBox("*I need to get over the bridge.");
		UI->addStringToChatBox("It is not safe in these woods.");
	}
}

void snowChestInteract(NPC* NPCPtr)
{
	UserInterface* UI{ NPCPtr->getWorld()->getUniverse()->getGame()->getUserInterface() };
	Inventory* inv{ NPCPtr->getWorld()->getUniverse()->getGame()->getPlayer()->getInventory() };
	if (!inv->isFull() && !inv->hasItem(4))
	{
		inv->addItem(4);
		NPCPtr->getWorld()->getUniverse()->getGame()->getApp()->getSoundHandler().playSound("itemAdded");
		Player* player{ NPCPtr->getWorld()->getUniverse()->getGame()->getPlayer() };
		player->setDamage(player->getDamage() + 10);
		UI->addStringToChatBox("*You find an amulet in the chest.");
	}
	else
	{
		UI->addStringToChatBox("*The chest is empty.");
	}
}

void world5GuyInteract(NPC* NPCPtr)
{
	UserInterface* UI{ NPCPtr->getWorld()->getUniverse()->getGame()->getUserInterface() };

	if (!(NPCPtr->getWorld()->getTileVector().at(51 * NPCPtr->getWorld()->getMapWidth() + 26) == 900))
	{
		UI->addStringToChatBox("*The wizard gave me a Magic Orb,");
		UI->addStringToChatBox("look what I can do!");

		NPCPtr->getWorld()->changeTile(51 * NPCPtr->getWorld()->getMapWidth() + 26, 900);
		NPCPtr->getWorld()->getUniverse()->addEnemy(5, new Enemy(1, 0, 0, 5, "fire", sf::Vector2f(26 * Tile::TILESIZE, 51 * Tile::TILESIZE), NPCPtr->getWorld()->getUniverse()->getWorld(5), NPCPtr->getWorld()->getUniverse()->getGame()->getTexture("fire"), fireDeath));
		NPCPtr->getWorld()->changeTile(48 * NPCPtr->getWorld()->getMapWidth() + 27, 900);
		NPCPtr->getWorld()->getUniverse()->addEnemy(5, new Enemy(1, 0, 0, 6, "fire", sf::Vector2f(27 * Tile::TILESIZE, 48 * Tile::TILESIZE), NPCPtr->getWorld()->getUniverse()->getWorld(5), NPCPtr->getWorld()->getUniverse()->getGame()->getTexture("fire"), fireDeath));
		NPCPtr->getWorld()->changeTile(49 * NPCPtr->getWorld()->getMapWidth() + 27, 900);
		NPCPtr->getWorld()->getUniverse()->addEnemy(5, new Enemy(1, 0, 0, 7, "fire", sf::Vector2f(27 * Tile::TILESIZE, 49 * Tile::TILESIZE), NPCPtr->getWorld()->getUniverse()->getWorld(5), NPCPtr->getWorld()->getUniverse()->getGame()->getTexture("fire"), fireDeath));
		NPCPtr->getWorld()->changeTile(50 * NPCPtr->getWorld()->getMapWidth() + 27, 900);
		NPCPtr->getWorld()->getUniverse()->addEnemy(5, new Enemy(1, 0, 0, 8, "fire", sf::Vector2f(27 * Tile::TILESIZE, 50 * Tile::TILESIZE), NPCPtr->getWorld()->getUniverse()->getWorld(5), NPCPtr->getWorld()->getUniverse()->getGame()->getTexture("fire"), fireDeath));
		NPCPtr->getWorld()->changeTile(50 * NPCPtr->getWorld()->getMapWidth() + 28, 900);
		NPCPtr->getWorld()->getUniverse()->addEnemy(5, new Enemy(1, 0, 0, 9, "fire", sf::Vector2f(28 * Tile::TILESIZE, 50 * Tile::TILESIZE), NPCPtr->getWorld()->getUniverse()->getWorld(5), NPCPtr->getWorld()->getUniverse()->getGame()->getTexture("fire"), fireDeath));
		NPCPtr->getWorld()->changeTile(51 * NPCPtr->getWorld()->getMapWidth() + 28, 900);
		NPCPtr->getWorld()->getUniverse()->addEnemy(5, new Enemy(1, 0, 0, 10, "fire", sf::Vector2f(28 * Tile::TILESIZE, 51 * Tile::TILESIZE), NPCPtr->getWorld()->getUniverse()->getWorld(5), NPCPtr->getWorld()->getUniverse()->getGame()->getTexture("fire"), fireDeath));

		UI->addStringToChatBox("Woops, I guess you must be careful!");
	}
	else
		UI->addStringToChatBox("*Be careful!");	
}

void superGhostDeath(Enemy * enemyPtr)
{
	UserInterface* UI{ enemyPtr->getWorld()->getUniverse()->getGame()->getUserInterface() };
	UI->addStringToChatBox("*You slayed the ghost and it");
	UI->addStringToChatBox("dropped a Magic Wet Chalice");
	enemyPtr->getWorld()->getUniverse()->getGame()->getPlayer()->getInventory()->addItem(6);
	enemyPtr->getWorld()->getUniverse()->getGame()->getApp()->getSoundHandler().playSound("itemAdded");
	enemyPtr->getWorld()->removeEnemy(enemyPtr);
}



void brokenFountainInteract1(NPC* NPCPtr)
{
	if (NPCPtr->getWorld()->getUniverse()->getGame()->getPlayer()->getInventory()->hasItem(6))
	{
		NPCPtr->getWorld()->getUniverse()->getGame()->getPlayer()->getInventory()->removeItem(6);

		UserInterface* UI{ NPCPtr->getWorld()->getUniverse()->getGame()->getUserInterface() };
		UI->addStringToChatBox("*You have repaired a fountain!");
		NPCPtr->getWorld()->changeTile(23 * NPCPtr->getWorld()->getMapWidth() + 33, 200);
		NPCPtr->getWorld()->getUniverse()->addEnemy(3, new Enemy(1, 1000, 25, 9, "superGhost", sf::Vector2f(37 * Tile::TILESIZE, 27 * Tile::TILESIZE), NPCPtr->getWorld()->getUniverse()->getWorld(3), NPCPtr->getWorld()->getUniverse()->getGame()->getTexture("superGhost"), superGhostDeath));
		NPCPtr->die();
	}
}
void brokenFountainInteract2(NPC* NPCPtr)
{
	if (NPCPtr->getWorld()->getUniverse()->getGame()->getPlayer()->getInventory()->hasItem(6))
	{
		NPCPtr->getWorld()->getUniverse()->getGame()->getPlayer()->getInventory()->removeItem(6);

		UserInterface* UI{ NPCPtr->getWorld()->getUniverse()->getGame()->getUserInterface() };
		UI->addStringToChatBox("*You have repaired a fountain!");
		NPCPtr->getWorld()->changeTile(23 * NPCPtr->getWorld()->getMapWidth() + 43, 200);
		NPCPtr->getWorld()->getUniverse()->addEnemy(3, new Enemy(1, 1000, 25, 9, "superGhost", sf::Vector2f(37 * Tile::TILESIZE, 27 * Tile::TILESIZE), NPCPtr->getWorld()->getUniverse()->getWorld(3), NPCPtr->getWorld()->getUniverse()->getGame()->getTexture("superGhost"), superGhostDeath));
		NPCPtr->die();
	}
}
void brokenFountainInteract3(NPC* NPCPtr)
{
	if (NPCPtr->getWorld()->getUniverse()->getGame()->getPlayer()->getInventory()->hasItem(6))
	{
		NPCPtr->getWorld()->getUniverse()->getGame()->getPlayer()->getInventory()->removeItem(6);

		UserInterface* UI{ NPCPtr->getWorld()->getUniverse()->getGame()->getUserInterface() };
		UI->addStringToChatBox("*You have repaired a fountain!");
		NPCPtr->getWorld()->changeTile(33 * NPCPtr->getWorld()->getMapWidth() + 33, 200);
		NPCPtr->getWorld()->getUniverse()->addEnemy(3, new Enemy(1, 1000, 25, 9, "superGhost", sf::Vector2f(37 * Tile::TILESIZE, 27 * Tile::TILESIZE), NPCPtr->getWorld()->getUniverse()->getWorld(3), NPCPtr->getWorld()->getUniverse()->getGame()->getTexture("superGhost"), superGhostDeath));
		NPCPtr->die();
	}
}
void brokenFountainInteract4(NPC* NPCPtr)
{
	Inventory* inv{ NPCPtr->getWorld()->getUniverse()->getGame()->getPlayer()->getInventory() };
	if (inv->hasItem(6))
	{
		inv->removeItem(6);

		UserInterface* UI{ NPCPtr->getWorld()->getUniverse()->getGame()->getUserInterface() };
		UI->addStringToChatBox("*You have repaired a fountain!");
		NPCPtr->getWorld()->changeTile(33 * NPCPtr->getWorld()->getMapWidth() + 43, 200);
		NPCPtr->getWorld()->getUniverse()->addEnemy(3, new Enemy(1, 1000, 25, 9, "superGhost", sf::Vector2f(37 * Tile::TILESIZE, 27 * Tile::TILESIZE), NPCPtr->getWorld()->getUniverse()->getWorld(3), NPCPtr->getWorld()->getUniverse()->getGame()->getTexture("superGhost"), superGhostDeath));
		NPCPtr->die();
	}
}

void FirimaniumsInteract(NPC* NPCPtr)
{
	UserInterface* UI{ NPCPtr->getWorld()->getUniverse()->getGame()->getUserInterface() };
	Inventory* inv{ NPCPtr->getWorld()->getUniverse()->getGame()->getPlayer()->getInventory() };
	if (!inv->isFull() && !inv->hasItem(5))
	{
		inv->addItem(5);
		NPCPtr->getWorld()->getUniverse()->getGame()->getApp()->getSoundHandler().playSound("itemAdded");
		UI->addStringToChatBox("*I am the mighty wizard Firimaniums!");
		UI->addStringToChatBox("I hear you are fighting Bad Alloc,");
		UI->addStringToChatBox("take this Magic Orb of Fire! See you!");
		UI->addStringToChatBox("(Press 'J' to use your new power)");

		NPCPtr->teleport(25 * Tile::TILESIZE, 26 * Tile::TILESIZE);
		NPCPtr->getWorld()->changeTile(25 * NPCPtr->getWorld()->getMapWidth() + 27, 0);
	}
	else
	{
	
		UI->addStringToChatBox("*I turn my back on you for two");
		UI->addStringToChatBox("seconds and you burn down my");
		UI->addStringToChatBox("house, nice to see you're putting");
		UI->addStringToChatBox("your Orb of Fire to good use!");
	}
}


void houseFireInteract(World* worldPtr)
{
	Inventory* inv{ worldPtr->getUniverse()->getGame()->getPlayer()->getInventory() };
	if (inv->hasItem(5) && !(worldPtr->getTileVector().at(28 * worldPtr->getMapWidth() + 15) == 901))
	{
		worldPtr->getUniverse()->addEnemy(5, new Enemy(1, 0, 0, 11, "fire", sf::Vector2f(15 * Tile::TILESIZE, 28 * Tile::TILESIZE), worldPtr, worldPtr->getUniverse()->getGame()->getTexture("fire"), fireDeath));
		worldPtr->getUniverse()->addEnemy(5, new Enemy(1, 0, 0, 12, "fire", sf::Vector2f(16 * Tile::TILESIZE, 28 * Tile::TILESIZE), worldPtr, worldPtr->getUniverse()->getGame()->getTexture("fire"), fireDeath));
		worldPtr->getUniverse()->addEnemy(5, new Enemy(1, 0, 0, 13, "fire", sf::Vector2f(17 * Tile::TILESIZE, 28 * Tile::TILESIZE), worldPtr, worldPtr->getUniverse()->getGame()->getTexture("fire"), fireDeath));
		worldPtr->getUniverse()->addEnemy(5, new Enemy(1, 0, 0, 14, "fire", sf::Vector2f(18 * Tile::TILESIZE, 28 * Tile::TILESIZE), worldPtr, worldPtr->getUniverse()->getGame()->getTexture("fire"), fireDeath));
		worldPtr->getUniverse()->addEnemy(5, new Enemy(1, 0, 0, 15, "fire", sf::Vector2f(15 * Tile::TILESIZE, 29 * Tile::TILESIZE), worldPtr, worldPtr->getUniverse()->getGame()->getTexture("fire"), fireDeath));
		worldPtr->getUniverse()->addEnemy(5, new Enemy(1, 0, 0, 16, "fire", sf::Vector2f(16 * Tile::TILESIZE, 29 * Tile::TILESIZE), worldPtr, worldPtr->getUniverse()->getGame()->getTexture("fire"), fireDeath));
		worldPtr->getUniverse()->addEnemy(5, new Enemy(1, 0, 0, 17, "fire", sf::Vector2f(17 * Tile::TILESIZE, 29 * Tile::TILESIZE), worldPtr, worldPtr->getUniverse()->getGame()->getTexture("fire"), fireDeath));
		worldPtr->getUniverse()->addEnemy(5, new Enemy(1, 0, 0, 18, "fire", sf::Vector2f(18 * Tile::TILESIZE, 29 * Tile::TILESIZE), worldPtr, worldPtr->getUniverse()->getGame()->getTexture("fire"), fireDeath));
		worldPtr->getUniverse()->addEnemy(5, new Enemy(1, 0, 0, 19, "fire", sf::Vector2f(15 * Tile::TILESIZE, 30 * Tile::TILESIZE), worldPtr, worldPtr->getUniverse()->getGame()->getTexture("fire"), fireDeath));
		worldPtr->getUniverse()->addEnemy(5, new Enemy(1, 0, 0, 20, "fire", sf::Vector2f(16 * Tile::TILESIZE, 30 * Tile::TILESIZE), worldPtr, worldPtr->getUniverse()->getGame()->getTexture("fire"), fireDeath));
		worldPtr->getUniverse()->addEnemy(5, new Enemy(1, 0, 0, 21, "fire", sf::Vector2f(17 * Tile::TILESIZE, 30 * Tile::TILESIZE), worldPtr, worldPtr->getUniverse()->getGame()->getTexture("fire"), fireDeath));
		worldPtr->getUniverse()->addEnemy(5, new Enemy(1, 0, 0, 22, "fire", sf::Vector2f(18 * Tile::TILESIZE, 30 * Tile::TILESIZE), worldPtr, worldPtr->getUniverse()->getGame()->getTexture("fire"), fireDeath));
		worldPtr->getUniverse()->addEnemy(5, new Enemy(1, 0, 0, 23, "fire", sf::Vector2f(15 * Tile::TILESIZE, 31 * Tile::TILESIZE), worldPtr, worldPtr->getUniverse()->getGame()->getTexture("fire"), fireDeath));
		worldPtr->getUniverse()->addEnemy(5, new Enemy(1, 0, 0, 24, "fire", sf::Vector2f(16 * Tile::TILESIZE, 31 * Tile::TILESIZE), worldPtr, worldPtr->getUniverse()->getGame()->getTexture("fire"), fireDeath));
		worldPtr->getUniverse()->addEnemy(5, new Enemy(1, 0, 0, 25, "fire", sf::Vector2f(17 * Tile::TILESIZE, 31 * Tile::TILESIZE), worldPtr, worldPtr->getUniverse()->getGame()->getTexture("fire"), fireDeath));
		worldPtr->getUniverse()->addEnemy(5, new Enemy(1, 0, 0, 26, "fire", sf::Vector2f(18 * Tile::TILESIZE, 31 * Tile::TILESIZE), worldPtr, worldPtr->getUniverse()->getGame()->getTexture("fire"), fireDeath));

		worldPtr->changeTile(28 * worldPtr->getMapWidth() + 15, 901);
		worldPtr->changeTile(28 * worldPtr->getMapWidth() + 16, 901);
		worldPtr->changeTile(28 * worldPtr->getMapWidth() + 17, 901);
		worldPtr->changeTile(28 * worldPtr->getMapWidth() + 18, 901);
		worldPtr->changeTile(29 * worldPtr->getMapWidth() + 15, 901);
		worldPtr->changeTile(29 * worldPtr->getMapWidth() + 16, 901);
		worldPtr->changeTile(29 * worldPtr->getMapWidth() + 17, 901);
		worldPtr->changeTile(29 * worldPtr->getMapWidth() + 18, 901);
		worldPtr->changeTile(30 * worldPtr->getMapWidth() + 15, 901);
		worldPtr->changeTile(30 * worldPtr->getMapWidth() + 16, 901);
		worldPtr->changeTile(30 * worldPtr->getMapWidth() + 17, 901);
		worldPtr->changeTile(30 * worldPtr->getMapWidth() + 18, 901);
		worldPtr->changeTile(31 * worldPtr->getMapWidth() + 15, 901);
		worldPtr->changeTile(31 * worldPtr->getMapWidth() + 16, 901);
		worldPtr->changeTile(31 * worldPtr->getMapWidth() + 17, 901);
		worldPtr->changeTile(31 * worldPtr->getMapWidth() + 18, 901);
	}
}



