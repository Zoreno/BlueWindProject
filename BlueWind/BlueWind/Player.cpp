#include "Player.h"
#include "World.h"
#include "Universe.h"
#include "Game.h"
#include "Frame.h"
#include "Application.h"
#include "Input.h"
#include <map>
#include <math.h>
#include "GameOver.h"
#include <algorithm>

using namespace std;


Player::Player(World * worldPtr, sf::Texture& texture, Game* game)
	: Entity(1, 100, 10, 0, "Kalle", sf::Vector2f(2 * 32, 2 * 32), worldPtr, game->getTexture("player")),
	mana_{ 20 }, 
	maxMana_{ 20 }, 
	gamePointer_{ game }, 
	inventory_{ this,game }
{
	
}

int Player::getExperience() const
{
	return experience_;
}

void Player::addExperience(int value)
{
	experience_ += value;
	while(checkForLevelup())
	{
		maxHealth_ += 20;
		health_ = maxHealth_;
		maxMana_ += 10;
		mana_ = maxMana_;
		damage_ += 10;
	}
}

int Player::getMana() const
{
	return mana_;
}

void Player::setMana(int value)
{
	mana_ = value;
}

void Player::addMana(int value)
{
	mana_ = min(mana_ + value, maxMana_);
}

int Player::getMaxMana() const
{
	return maxMana_;
}

void Player::setMaxMana(int value)
{
	maxMana_ = value;
	mana_ = value;
}

int Player::getMaxExperience()
{
	return getXpToLevel();
}

void Player::setName(std::string name)
{
	name_ = name;
}

void Player::setMaxHealth(int value)
{
	maxHealth_ = value;
	health_ = value;
}

void Player::setDamage(int value)
{
	damage_ = value;
}

void Player::setLevel(int value)
{
	level_ = value;
}

void Player::setExperience(int value)
{
	experience_ = value;
}

Inventory* Player::getInventory()
{
	return &inventory_;
}


void Player::attack(const map<int, Enemy*>& enemies)
{
	if (mana_ < 5) return;
	mana_ -= 5;
	state_ = attacking;
	for (auto it : enemies)
	{
		if (getDistance(position_, it.second->getPosition()) <= 32)
		{
			it.second->removeHealth(damage_); 
			break;
		}
	}

}

int Player::getXpToLevel()
{
	return static_cast<int>(std::floor( 100 * std::pow(1.15f, level_)));
}

bool Player::checkForLevelup()
{
	if (experience_ >= getXpToLevel())
	{
		experience_ -= getXpToLevel();
		level_++;
		return true;
	}
	return false;
}

void Player::update()
{
	//TODO balansera lite
	//addHealth(1);
	addMana(1);
	if (state_ == attacking)
	{
		anim_.update(state_, dir_, walking_);
		if (attackCounter % 15 == 14)
		{
			state_ = walking1;
			attackCounter = 0;
		}
		attackCounter++;
		return;
	}
	walking_ = false;
	if (gamePointer_->getApp()->getInput().pressedButtons_.at('a'))
	{
		move(-1, 0);
	}
	if (gamePointer_->getApp()->getInput().pressedButtons_.at('d'))
	{
		move(1, 0);		
	}
	if (gamePointer_->getApp()->getInput().pressedButtons_.at('s'))
	{
		move(0, 1);		
	}
	if (gamePointer_->getApp()->getInput().pressedButtons_.at('w'))
	{
		move(0, -1);		
	}
	anim_.update(state_, dir_, walking_);
	checkSensors();
}

void Player::render(GameWindow & window)
{
	anim_.render(window);
}


void Player::die()
{
	gamePointer_->getApp()->setNextFrame(new GameOver(gamePointer_->getApp()));
}


void Player::checkSensors()
{
	for (auto it : worldPointer_->getSensorVector())
	{
		if (getDistance(position_, it.second->getPosition()) <= 32)
		{
			it.second->trigger();
			break;
		}
	}
}

