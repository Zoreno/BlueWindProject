#include "Enemy.h"
#include "World.h"
#include "Universe.h"
#include "Game.h"
#include <iostream>

using namespace std;

Enemy::Enemy(int level, int health, int damage, int ID, std::string name, sf::Vector2f position, World * worldPtr, sf::Texture& texture)
	: Entity(level,health,damage,ID,name,position,worldPtr), startPosition_{position}
{
	sprite_.setOrigin(sf::Vector2f(0.0f, 0.0f));
	sprite_.setTexture(texture);
}

void Enemy::update()
{
	//cout << "Enemy uppdaterar" << endl;
	updateState();
	executeState();
}

void Enemy::render(GameWindow & window)
{
	//cout << "Enemy render" << endl;
	sprite_.setPosition(position_);
	window.draw(sprite_);
}

void Enemy::updateState()
{
	sf::Vector2f playerPos = worldPointer_->getUniverse()->getGame()->getPlayer()->getPosition();
	float playerDistance = getDistance(position_, playerPos);
	float startDistance = getDistance(position_, startPosition_);
	if ((startDistance < 1) && state_ == RESET)
	{
		state_ = IDLE;
		cout << "Här sätts Idle" << endl;
	}
	else if (((startDistance > 80) || (playerDistance > 80)) && state_ != IDLE)
	{
		state_ = RESET;
		cout << "Här sätts Reset" << endl;
	}
	else if ((playerDistance <= 8) && (state_ == MOVETOPLAYER))
	{
		state_ = ATTACK;
		cout << "Här sätts Attack" << endl;
	}
	else if ((playerDistance <= 80) && (playerDistance > 8) && (state_ == IDLE || state_ ==  ATTACK))
	{
		state_ = MOVETOPLAYER;
		cout << "Här sätts MoveToPlayer" << endl;
	}
	//else 
}

void Enemy::executeState()
{
	//TODO
	sf::Vector2f playerPos = worldPointer_->getUniverse()->getGame()->getPlayer()->getPosition();
	sf::Vector2f returnVector;
	sf::Vector2f toPlayerVector;
	switch (state_)
	{
	case IDLE:
		break;
	case RESET:
		health_ = maxHealth_;
		returnVector = normalize(startPosition_ - position_);
		move(returnVector.x, returnVector.y);
		break;
	case ATTACK:
		attackPlayer();
		break;
	case MOVETOPLAYER:
		toPlayerVector = normalize(playerPos - position_);
		move(toPlayerVector.x, toPlayerVector.y);
		break;
	}
}

void Enemy::attackPlayer()
{
	if (attackCooldown_ >= 60)
	{
		worldPointer_->getUniverse()->getGame()->getPlayer()->removeHealth(damage_);
		attackCooldown_ = 0;
		return;
	}
	attackCooldown_++;
}

float getDistance(sf::Vector2f vec1, sf::Vector2f vec2)
{
	sf::Vector2f vec = vec2 - vec1;
	return sqrt(vec.x*vec.x + vec.y*vec.y);
}

sf::Vector2f normalize(sf::Vector2f vec)
{
	int x = vec.x;
	int y = vec.y;

	if (x != 0)
	{
		x /= abs(x);
	}

	if (y != 0)
	{
		y /= abs(y);
	}

	return sf::Vector2f(x,y);
}
