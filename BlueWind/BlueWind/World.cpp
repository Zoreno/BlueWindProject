#include "World.h"
#include "Universe.h"
#include <iostream>

using namespace std;

World::World(int ID, Universe * universePtr, std::string mapFile)
	: ID_{ID}, universePointer_{universePtr}
{
	loadWorld(mapFile);
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
	//cout << "World renderar" << endl;
	sf::View view = window.getView();
	int startX = (view.getCenter().x - (20 * Tile::TILESIZE)) / Tile::TILESIZE;
	int endX = (view.getCenter().x + (20 * Tile::TILESIZE)) / Tile::TILESIZE;
	int startY = (view.getCenter().y - (20 * Tile::TILESIZE)) / Tile::TILESIZE;
	int endY = (view.getCenter().y + (20 * Tile::TILESIZE)) / Tile::TILESIZE;

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
	//cout << startX << "," << startY << "," << endX << "," << endY << endl;
	for (int y = startY; y < endY; ++y)
	{
		for (int x = startX; x < endX; ++x)
		{
			universePointer_->getTile(tileVector_.at(x + mapWidth*y)).render(window, x, y);
		}
	}
	//cout << "World renderar klart" << endl;

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
	if (!(pos > tileVector_.size()))
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
	default:
		cout << "Fel färg!" << endl;
		return -1;
		//TODO kasta exception. Färgen finns inte! Bra Jobbat hörru.
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
