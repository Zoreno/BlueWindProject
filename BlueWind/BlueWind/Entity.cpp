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

void Entity::move(float dx, float dy)
{
	sf::Vector2f upper_left = sf::Vector2f(position_) + sf::Vector2f(dx, dy);
	sf::Vector2f bottom_left = sf::Vector2f(position_.x, position_.y + Tile::TILESIZE-1) + sf::Vector2f(dx, dy);
	sf::Vector2f upper_right = sf::Vector2f(position_.x + Tile::TILESIZE-1, position_.y) + sf::Vector2f(dx, dy);
	sf::Vector2f bottom_right = sf::Vector2f(position_.x + Tile::TILESIZE-1, position_.y + Tile::TILESIZE-1) + sf::Vector2f(dx, dy);

	int mapWidth = worldPointer_->getMapWidth();
	int mapHeight = worldPointer_->getMapHeight();

	unsigned int cornerTopLeft = static_cast<unsigned int>(floor(upper_left.x / Tile::TILESIZE) + mapWidth*floor(upper_left.y / Tile::TILESIZE));
	unsigned int cornerTopRight = static_cast<unsigned int>(floor(bottom_left.x / Tile::TILESIZE) + mapWidth*floor(bottom_left.y / Tile::TILESIZE));
	unsigned int cornerBottomLeft = static_cast<unsigned int>(floor(upper_right.x / Tile::TILESIZE) + mapWidth*floor(upper_right.y / Tile::TILESIZE));
	unsigned int cornerBottomRight = static_cast<unsigned int>(floor(bottom_right.x / Tile::TILESIZE) + mapWidth*floor(bottom_right.y / Tile::TILESIZE));

	bool upper_left_walkable = worldPointer_->getUniverse()->getTile(worldPointer_->getTileVector().at(cornerTopLeft)).isWalkable();
	bool bottom_left_walkable = worldPointer_->getUniverse()->getTile(worldPointer_->getTileVector().at(cornerTopRight)).isWalkable();
	bool upper_right_walkable = worldPointer_->getUniverse()->getTile(worldPointer_->getTileVector().at(cornerBottomLeft)).isWalkable();
	bool bottom_right_walkable = worldPointer_->getUniverse()->getTile(worldPointer_->getTileVector().at(cornerBottomRight)).isWalkable();
	
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

void Entity::teleport(float x, float y)
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

const sf::Vector2f Entity::getPosition() const
{
	return position_;
}

World * Entity::getWorld() const
{
	return worldPointer_;
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

