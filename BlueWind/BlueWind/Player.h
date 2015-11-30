#pragma once

#include "Entity.h"
#include "Inventory.h"
#include <map>
//#include "Animation.h"

class World;
class Game;
class Enemy;

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

	void attack(const std::map<int, Enemy*>);

	int getXpToLevel();
	bool checkForLevelup();

	void update() override;
	void render(GameWindow&) override;

	void die() override;

private:
	int experience_{ 0 };
	int mana_;
	int maxMana_;
	Game* gamePointer_;
	Inventory inventory_;
	int attackCounter;
	//Animation anim_;
	//sf::Sprite sprite_;
};