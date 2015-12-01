#include "Entity.h"
#include "World.h"
#include "Universe.h"
#include "Game.h"
#include "Tile.h"
#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;


Entity::Entity(int level, int health, int damage, int ID, std::string name, sf::Vector2f position, World * worldPtr, sf::Texture& tex)
	:level_{ level }, 
	health_{ health }, 
	maxHealth_{ health }, 
	damage_{ damage }, 
	ID_{ ID }, 
	name_{name}, 
	position_{position}, 
	worldPointer_{worldPtr},  
	anim_{ this, tex }
{}

void Entity::move(int dx, int dy)
{
	sf::Vector2f upper_left = sf::Vector2f(position_) + sf::Vector2f(dx, dy);
	sf::Vector2f bottom_left = sf::Vector2f(position_.x, position_.y + Tile::TILESIZE-1) + sf::Vector2f(dx, dy);
	sf::Vector2f upper_right = sf::Vector2f(position_.x + Tile::TILESIZE-1, position_.y) + sf::Vector2f(dx, dy);
	sf::Vector2f bottom_right = sf::Vector2f(position_.x + Tile::TILESIZE-1, position_.y + Tile::TILESIZE-1) + sf::Vector2f(dx, dy);

	int mapWidth = worldPointer_->getMapWidth();
	int mapHeight = worldPointer_->getMapHeight();

	bool upper_left_walkable = worldPointer_->getUniverse()->getTile(worldPointer_->getTileVector().at(floor(upper_left.x / Tile::TILESIZE) + mapWidth*floor(upper_left.y / Tile::TILESIZE))).walkable_;
	bool bottom_left_walkable = worldPointer_->getUniverse()->getTile(worldPointer_->getTileVector().at(floor(bottom_left.x / Tile::TILESIZE) + mapWidth*floor(bottom_left.y / Tile::TILESIZE))).walkable_;
	bool upper_right_walkable = worldPointer_->getUniverse()->getTile(worldPointer_->getTileVector().at(floor(upper_right.x / Tile::TILESIZE) + mapWidth*floor(upper_right.y / Tile::TILESIZE))).walkable_;
	bool bottom_right_walkable = worldPointer_->getUniverse()->getTile(worldPointer_->getTileVector().at(floor(bottom_right.x / Tile::TILESIZE) + mapWidth*floor(bottom_right.y / Tile::TILESIZE))).walkable_;
	
	if(upper_left_walkable && bottom_left_walkable && upper_right_walkable && bottom_right_walkable)
	position_ += sf::Vector2f(dx, dy);

	if (dx < 0)
	{
		walking_ = true;
		dir_ = west;
	}
	else if (dx > 0)
	{
		walking_ = true;
		dir_ = east;
	}
	else if (dy > 0)
	{
		walking_ = true;
		dir_ = south;
	}
	else if (dy < 0)
	{
		walking_ = true;
		dir_ = north;
	}
}

void Entity::teleport(int x, int y)
{
	position_ = sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
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

const sf::Vector2f Entity::getPosition() const
{
	return position_;
}

void Entity::setCurrentWorld(World * worldPtr)
{
	worldPointer_ = worldPtr;
}

void Entity::addHealth(int value)
{
	health_ = min(health_ + value, maxHealth_);
}

void Entity::removeHealth(int value)
{
	health_ -= value;
	if (health_ <= 0)
	{
		health_ = 0;
		die();
	}
	cout << "Damage taken. Current health: " << health_ << endl;
}

void Entity::die()
{
	cout << "Entity died" << endl; 
}

