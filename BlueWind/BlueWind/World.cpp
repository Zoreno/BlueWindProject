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
}

void World::render(GameWindow & window)
{
	cout << "World renderar" << endl;
	sf::View view = window.getView();
	int startX = (view.getCenter().x - (20 * 16)) / 16;
	int endX = (view.getCenter().x + (20 * 16)) / 16;
	int startY = (view.getCenter().y - (20 * 16)) / 16;
	int endY = (view.getCenter().y + (20 * 16)) / 16;

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
	cout << startX << "," << startY << "," << endX << "," << endY << endl;
	for (int y = startY; y < endY; ++y)
	{
		for (int x = startX; x < endX; ++x)
		{
			universePointer_->getTile(tileVector_.at(x + mapWidth*y)).render(window, x, y);
		}
	}
	cout << "World renderar klart" << endl;
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

const int World::getID() const
{
	return ID_;
}

int World::getIntFromColor(sf::Color color)
{

	switch (color.toInteger())
	{
	case 0x00FF00FF:
		return 0;
	case 0xFF0000FF:
		return 1;
	default:
		cout << "Fel färg!" << endl;
		return -1;
		//TODO kasta exception. Färgen finns inte! Bra Jobbat hörru.
	}
}
