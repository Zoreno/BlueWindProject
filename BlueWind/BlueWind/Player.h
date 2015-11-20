#pragma once

#include "Entity.h"

class World;

class Player : public Entity
{
public:
	Player(World*, sf::Texture&);
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

	void update() override;
	void render(GameWindow&) override;

	//int enemyClose();

private:
	int experience_{ 0 };
	int mana_;
	int maxMana_;
	int maxExperience_; //Temporär


	sf::Sprite sprite_;
};