#pragma once

#include "Entity.h"
#include "GameWindow.h"

float getDistance(sf::Vector2f, sf::Vector2f);
sf::Vector2f normalize(sf::Vector2f);

class Enemy : public Entity
{
public:
	enum STATES { ATTACK, MOVETOPLAYER, IDLE, RESET };

	Enemy(int, int, int, int, std::string, sf::Vector2f, World*, sf::Texture&);
	Enemy() = delete;
	Enemy(const Enemy&) = delete;
	Enemy& operator=(const Enemy&) = delete;

	void update() override;
	void render(GameWindow&) override;

	void die() override;
private:
	const sf::Vector2f startPosition_;
	STATES state_{ IDLE };

	int attackCooldown_{ 0 };
	int resetTimer_{ 0 };
	sf::Sprite sprite_;

	void updateState();
	void executeState();

	void attackPlayer();
};