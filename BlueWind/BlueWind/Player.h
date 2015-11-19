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

	void update() override;
	void render(GameWindow&) override;

	bool enemyClose();

private:
	int experience_;

	sf::Sprite sprite_;
};