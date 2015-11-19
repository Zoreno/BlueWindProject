#pragma once

#include "GameWindow.h"
#include <string>
#include <SFML\Graphics.hpp>

class World;

class Entity
{
public:
	Entity(int, int, int, int, std::string, sf::Vector2f, World*);

	Entity(const Entity&) = delete;
	Entity() = delete;
	Entity& operator= (const Entity&) = delete;

	virtual void update() = 0;
	virtual void render(GameWindow&) = 0;

	void move(int, int);
	void teleport(int, int);
	
	int getLevel() const;
	int getHealth() const;
	int getMaxHealth() const;
	int getDamage() const;
	int getID() const;
	std::string getName() const;
	sf::Vector2f getPosition() const;

	void addHealth(int);
	void removeHealth(int);

	virtual void die();

protected:
	bool toBeRemoved{ false };
	int level_;
	int health_;
	int maxHealth_;
	int damage_;
	int ID_;
	std::string name_;
	sf::Vector2f position_;
	World* worldPointer_;
};