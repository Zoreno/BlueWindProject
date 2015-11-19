#include "Entity.h"
#include "World.h"
#include "Universe.h"
#include "Game.h"
#include "Tile.h"
#include <iostream>
#include <math.h>

using namespace std;


Entity::Entity(int level, int health, int damage, int ID, std::string name, sf::Vector2f position, World * worldPtr)
	:level_{ level }, health_{ health }, maxHealth_{ health }, damage_{ damage }, ID_{ ID }, name_{name}, position_{position}, worldPointer_{worldPtr}
{}

void Entity::move(int dx, int dy)
{
	sf::Vector2f upper_left = sf::Vector2f(position_) + sf::Vector2f(dx, dy);
	sf::Vector2f bottom_left = sf::Vector2f(position_.x, position_.y + 15)  + sf::Vector2f(dx, dy);
	sf::Vector2f upper_right = sf::Vector2f(position_.x + 15, position_.y) + sf::Vector2f(dx, dy);
	sf::Vector2f bottom_right = sf::Vector2f(position_.x + 15, position_.y + 15) + sf::Vector2f(dx, dy);

	int mapWidth = worldPointer_->getMapWidth();
	int mapHeight = worldPointer_->getMapHeight();

	//cout << "x:" << upper_left.x << endl;
	//cout << "y:" << upper_left.y << endl;
	//cout << worldPointer_->getUniverse()->getTile(worldPointer_->getTileVector().at(floor((upper_left.x / 1 + ((mapWidth)*upper_left.y) / 1) / 16))).walkable_ << endl;

	bool upper_left_walkable = worldPointer_->getUniverse()->getTile(worldPointer_->getTileVector().at(floor(upper_left.x / 16) + mapWidth*floor(upper_left.y / 16))).walkable_;
	bool bottom_left_walkable = worldPointer_->getUniverse()->getTile(worldPointer_->getTileVector().at(floor(bottom_left.x / 16) + mapWidth*floor(bottom_left.y / 16))).walkable_;
	bool upper_right_walkable = worldPointer_->getUniverse()->getTile(worldPointer_->getTileVector().at(floor(upper_right.x / 16) + mapWidth*floor(upper_right.y / 16))).walkable_;
	bool bottom_right_walkable = worldPointer_->getUniverse()->getTile(worldPointer_->getTileVector().at(floor(bottom_right.x / 16) + mapWidth*floor(bottom_right.y / 16))).walkable_;
	
	if(upper_left_walkable && bottom_left_walkable && upper_right_walkable && bottom_right_walkable)
	position_ += sf::Vector2f(dx, dy);
}

void Entity::teleport(int x, int y)
{
	position_ = sf::Vector2f(x, y);
}

int Entity::getLevel() const
{
	return level_;
}

int Entity::getHealth() const
{
	return health_;
}

int Entity::getMaxHealth() const
{
	return maxHealth_;
}

int Entity::getDamage() const
{
	return damage_;
}

int Entity::getID() const
{
	return ID_;
}

std::string Entity::getName() const
{
	return name_;
}

sf::Vector2f Entity::getPosition() const
{
	return position_;
}

void Entity::addHealth(int value)
{
	//TODO jonas fixar.
	health_ += value;
	if (health_ > maxHealth_)
	{
		health_ = maxHealth_;
	}
}

void Entity::removeHealth(int value)
{
	health_ -= value;
	if (health_ <= 0)
	{
		die();
	}
	cout << "Damage taken. Current health: " << health_ << endl;
}

void Entity::die()
{
	cout << "U dieded" << endl;
}
