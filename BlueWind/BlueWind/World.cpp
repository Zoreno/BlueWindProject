#include "World.h"
#include "Universe.h"
#include <iostream>

using namespace std;

World::World(int ID, Universe * universePtr, std::string mapFile, string music)
	: ID_{ ID },
	universePointer_{ universePtr },
	music_{music}
{
	loadWorld(mapFile);
}

World::~World()
{
	universePointer_ = nullptr;
	while (!enemyVector_.empty())
	{
		auto it = enemyVector_.begin();
		delete it->second;
		enemyVector_.erase(it);
	}
	while (!NPCVector_.empty())
	{
		auto it = NPCVector_.begin();
		delete it->second;
		NPCVector_.erase(it);
	}
	while (!sensorVector_.empty())
	{
		auto it = sensorVector_.begin();
		delete it->second;
		sensorVector_.erase(it);
	}
}



void World::update()
{
	for (auto it : enemyVector_)
	{
		it.second->update();
	}
	updateLists();
}

void World::render(GameWindow & window)
{
	sf::View view = window.getView();
	int startX = (static_cast<int>(view.getCenter().x) - (20 * Tile::TILESIZE)) / Tile::TILESIZE;
	int endX = (static_cast<int>(view.getCenter().x) + (20 * Tile::TILESIZE)) / Tile::TILESIZE;
	int startY = (static_cast<int>(view.getCenter().y) - (20 * Tile::TILESIZE)) / Tile::TILESIZE;
	int endY = (static_cast<int>(view.getCenter().y) + (20 * Tile::TILESIZE)) / Tile::TILESIZE;

	if (startX > mapWidth)
		startX = mapWidth;
	if (startX < 0)
		startX = 0;

	if (endX > mapWidth)
		endX = mapWidth;
	if (endX < 0)
		endX = 0;

	if (startY > mapHeight)
		startY = mapHeight;
	if (startY < 0)
		startY = 0;

	if (endY > mapHeight)
		endY = mapHeight;
	if (endY < 0)
		endY = 0;
	for (int y = startY; y < endY; ++y)
	{
		for (int x = startX; x < endX; ++x)
		{
			universePointer_->getTile(tileVector_.at(x + mapWidth*y)).render(window, x, y);
		}
	}

	for (auto it : enemyVector_)
	{
		it.second->render(window);
	}

	for (auto it : NPCVector_)
	{
		it.second->render(window);
	}

}

void World::loadWorld(std::string mapFile)
{
	sf::Image image;
	if (!image.loadFromFile(mapFile))
	{
		//TODO Kasta exception
	}

	mapWidth = image.getSize().x;
	mapHeight = image.getSize().y;
	for (int y{ 0 }; y < mapHeight; ++y)
	{
		for (int x{ 0 }; x < mapWidth; ++x)
		{
			tileVector_.push_back(getIntFromColor(image.getPixel(x, y)));
		}
	}
}

void World::addEnemy(Enemy * enemyPtr)
{
	cout << "Adding enemy in world " << ID_ << endl;
	enemyVector_.emplace(enemyPtr->getID(),enemyPtr);
}

void World::addNPC(NPC * NPCPtr)
{
	cout << "Adding NPC in world " << ID_ << endl;
	NPCVector_.emplace(NPCPtr->getID(), NPCPtr);
}

void World::addSensor(Sensor* sensorPtr)
{
	cout << "Adding Sensor in world " << ID_ << endl;
	sensorVector_.emplace(sensorPtr->getID(), sensorPtr);
}

void World::removeEnemy(Enemy * enemyPtr)
{
	removeEnemyVector_.push_back(enemyPtr->getID());
}

void World::removeNPC(NPC * NPCPtr)
{
	removeNPCVector_.push_back(NPCPtr->getID());
}

void World::removeSensor(Sensor* sensorPtr)
{
	removeSensorVector_.push_back(sensorPtr->getID());
}

void World::changeTile(int pos, int value)
{
	if (pos < 0)
	{
		return;
		//TODO Kanske exception.
	}
	
	if (!(static_cast<unsigned int>(pos) > tileVector_.size()))
	{
		tileVector_.at(pos) = value;	
	}
}

Universe * World::getUniverse() const
{
	return universePointer_;
}

const int World::getID() const
{
	return ID_;
}

const std::string World::getMusic()
{
	return music_;
}

const int World::getMapWidth() const
{
	return mapWidth;
}

const int World::getMapHeight() const
{
	return mapHeight;
}

const std::vector<int> World::getTileVector() const
{
	return tileVector_;
}

const std::map<int,NPC*> World::getNPCVector() const
{
	return NPCVector_;
}

const std::map<int, Sensor*> World::getSensorVector() const
{
	return sensorVector_;
}

const std::map<int,Enemy*> World::getEnemyVector() const
{
	return enemyVector_;
}

int World::getIntFromColor(sf::Color color)
{

	switch (color.toInteger())
	{
	case 0x00FF00FF: //Gräs
		return 0;
	case 0xFF0000FF: //Träd
		return 1;
	case 0x7F6A00FF: //Bro
		return 2;	
	case 0xB24400FF: //Hus00
		return 3;
	case 0xB24401FF: //Hus10
		return 4;
	case 0xB24402FF: //Hus01
		return 5;
	case 0xB24403FF: //Hus11
		return 6;
	case 0x7F7F7FFF: //Berg
		return 7;
	case 0x0000FFFF: //Vatten
		return 8;
	case 0xFF7F00FF: //Stubbe
		return 9;
	case 0x00FFFFFF : //is
		return 10;
	case 0xFFFF00FF : //snowTree
		return 23;
	case 0xFF006EFF: //cactus
		return 24;
	case 0xFF6A00FF: //sand
		return 25;
	case 0x404040FF: //palmtree
		return 26;

	default:
		cout << "Fel färg!" << endl;
		return -1;
	}
}

void World::updateLists()
{
	for (auto iter : removeEnemyVector_)
	{
		auto it = enemyVector_.find(iter);
		delete (it->second);
		enemyVector_.erase(it);
	}
	removeEnemyVector_.clear();

	for (auto iter : removeNPCVector_)
	{
		auto it = NPCVector_.find(iter);
		delete (it->second);
		NPCVector_.erase(it);
	}
	removeNPCVector_.clear();

	for (auto iter : removeSensorVector_)
	{
		auto it = sensorVector_.find(iter);
		delete (it->second);
		sensorVector_.erase(it);
	}
	removeSensorVector_.clear();
	
}
