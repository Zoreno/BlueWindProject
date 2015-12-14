#include "Enemy.h"
#include "World.h"
#include "Universe.h"
#include "Game.h"
#include <iostream>

using namespace std;

Enemy::Enemy(int level, int health, int damage, int ID, std::string name, sf::Vector2f position, World * worldPtr, sf::Texture& texture, std::function<void(Enemy*)> callbackFunc)
	: Entity(level,health,damage,ID,name,position,worldPtr, texture), startPosition_{position}, callback_{ callbackFunc }
{
	sprite_.setOrigin(sf::Vector2f(0.0f, 0.0f));
	sprite_.setTexture(texture);
}

void Enemy::update()
{
	updateState();
	executeState();
	anim_.update(animState_, dir_, walking_);
}

void Enemy::render(GameWindow & window)
{
	anim_.render(window);
	sf::RectangleShape hpBar{ sf::Vector2f(32 * ((float)health_ / (float)maxHealth_), 8) };
	hpBar.setPosition(position_ + sf::Vector2f(0, -8));
	hpBar.setFillColor(sf::Color::Red);
	window.draw(hpBar);
}

//void Enemy::die()
//{
//	cout << "Enemy died!" << endl;
//	worldPointer_->getUniverse()->getGame()->getPlayer()->addExperience(20);
//	worldPointer_->removeEnemy(this);
//}

void Enemy::die()
{
	callback_(this);
}

void Enemy::updateState()
{
	sf::Vector2f playerPos = worldPointer_->getUniverse()->getGame()->getPlayer()->getPosition();
	float playerDistance = getDistance(position_, playerPos);
	float startDistance = getDistance(position_, startPosition_);

	switch (state_)
	{
	case IDLE:
		if (playerDistance <= 160)
		{
			state_ = MOVETOPLAYER;
		}
		break;

	case RESET:
		if (startDistance < 2)
		{
			state_ = IDLE;
			walking_ = false;
		}
		break;

	case ATTACK:
		if (startDistance > 160 || playerDistance > 160)
		{
			state_ = RESET;
		}
		else if (playerDistance > 32)
		{
			state_ = MOVETOPLAYER;
		}
		break;

	case MOVETOPLAYER:
		if (startDistance > 160 || playerDistance > 160)
		{
			state_ = RESET;
		}
		else if (playerDistance <= 32)
		{
			state_ = ATTACK;
		}
		break;

	}
}

void Enemy::executeState()
{
	const sf::Vector2f playerPos = worldPointer_->getUniverse()->getGame()->getPlayer()->getPosition();
	sf::Vector2f returnVector;
	sf::Vector2f toPlayerVector;
	sf::Vector2f toStartVector;
	switch (state_)
	{
	case IDLE:
		resetTimer_ = 0;
		break;
	case RESET:
		health_ = maxHealth_;
		if (resetTimer_ >= 300)
		{
			teleport((startPosition_.x), (startPosition_.y));
		}
		else
		{
			resetTimer_++;
			toStartVector = normalize(startPosition_ - position_);
			move(2.0f*toStartVector.x, 2.0f*toStartVector.y);
		}
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
		animState_ = Entity::STATES::attacking;
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
	int x = static_cast<int>(vec.x);
	int y = static_cast<int>(vec.y);

	if (x != 0)
	{
		x /= abs(x);
	}

	if (y != 0)
	{
		y /= abs(y);
	}

	return sf::Vector2f(static_cast<float>(x),static_cast<float>(y));
}
