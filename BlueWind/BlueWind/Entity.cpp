#include "Entity.h"

Entity::Entity(int level, int health, int damage, int ID, std::string name, sf::Vector2f position, World * worldPtr)
	:level_{ level }, health_{ health }, maxHealth_{ health }, damage_{ damage }, ID_{ ID }, name_{name}, position_{position}, worldPointer_{worldPtr}
{}

void Entity::move(int dx, int dy)
{
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
}

void Entity::die()
{
	//TODO
}
