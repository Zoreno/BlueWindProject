#include "Sensor.h"
#include "World.h"
#include "Universe.h"
#include "Game.h"
#include <iostream>

using namespace std;

Sensor::Sensor(int ID, std::string name, sf::Vector2f position, World * worldPtr, std::function<void(World*)> callbackFunc, sf::Texture& tex)
	: Entity(0, 0, 0, ID, name, position, worldPtr, tex), callback_{ callbackFunc }
{
}

void Sensor::update()
{
}

void Sensor::render(GameWindow & window)
{
}

void Sensor::trigger()
{
	callback_(worldPointer_);
}

void Sensor::die()
{
}


