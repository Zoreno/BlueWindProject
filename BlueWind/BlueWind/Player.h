#pragma once

#include "Entity.h"
#include "Inventory.h"
#include "Animation.h"

class World;
class Game;

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
	int getMaxMana() const;
	void setMaxMana(int);
	int getMaxExperience();

	Inventory* getInventory();

	void update() override;
	void render(GameWindow&) override;
	const int getAttackCooldown() const;

	//int enemyClose();

private:
	int experience_{ 0 };
	int mana_;
	int maxMana_;
	int maxExperience_; //Temporär
	int attackCooldown_;
	Game* gamePointer_;
	Inventory inventory_;
	Animation anim_;
	//sf::Sprite sprite_;
};