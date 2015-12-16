#pragma once

#include <map>
#include "Entity.h"
#include "Inventory.h"

class World;
class Game;
class Enemy;
class NPC;

class Player : public Entity
{
public:
	Player(World*, sf::Texture&, Game*);
	Player(const Player&) = delete;
	Player() = delete;
	Player& operator=(const Player&) = delete;

	int getExperience() const;
	void addExperience(int);
	int getMana() const;
	void setMana(int);
	void addMana(int);
	int getMaxMana() const;
	void setMaxMana(int);
	int getMaxExperience();

	void setName(std::string);
	void setMaxHealth(int);
	void setDamage(int);
	void setLevel(int);
	void setExperience(int);

	Inventory* getInventory();

	void swordAttack(const std::map<int, Enemy*>&);
	void fireballAttack(const std::map<int, Enemy*>&);
	void interact(const std::map<int, NPC*>&);

	int getXpToLevel();
	bool checkForLevelup();

	void update() override;
	void render(GameWindow&) override;

	void die() override;

private:
	void checkSensors();

	int experience_{ 0 };
	int mana_;
	int maxMana_;
	Game* gamePointer_;
	Inventory inventory_;
	int healthCounter_;
	int manaCounter_;
};