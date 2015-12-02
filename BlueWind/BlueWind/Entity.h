#pragma once

#include "GameWindow.h"
#include <string>
#include <SFML\Graphics.hpp>
#include "Animation.h"

class World;

class Entity
{
	friend class Animation;
public:
	enum STATES { walking1 = 0x0,walking2 = 0x1, attacking = 0x2 };
	enum DIRECTION { north = 0x0, west = 0x2, east = 0x3, south = 0x1 };

	Entity(int, int, int, int, std::string, sf::Vector2f, World*, sf::Texture&);

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
	const sf::Vector2f getPosition() const;
	World* getWorld() const;

	void setCurrentWorld(World*);

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

	bool walking_;

	STATES animState_{ walking1 };
	DIRECTION dir_{ south };

	std::string name_;
	sf::Vector2f position_;
	World* worldPointer_;
	Animation anim_;
};