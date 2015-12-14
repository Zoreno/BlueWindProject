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

//TODO HP och Damage just nu för debug
Player::Player(World * worldPtr, sf::Texture& texture, Game* game)
	: Entity(1, 100, 10, 0, "Faranos", sf::Vector2f(20 * 32, 20* 32), worldPtr, game->getTexture("player")),
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


void Player::swordAttack(const map<int, Enemy*>& enemies)
{
	if (mana_ < 4) return;
	mana_ -= 4;
	animState_ = attacking;
	for (auto it : enemies)
	{
		if (getDistance(position_, it.second->getPosition()) <= 32)
		{
			if (dir_ == north && it.second->getPosition().y <= position_.y)
			{
				it.second->removeHealth(damage_);
				break;
			}
			else if (dir_ == west && it.second->getPosition().x <= position_.x)
			{
				it.second->removeHealth(damage_);
				break;
			}
			else if (dir_ == east && it.second->getPosition().x >= position_.x)
			{
				it.second->removeHealth(damage_);
				break;
			}
			else if (dir_ == south && it.second->getPosition().y >= position_.y)
			{
				it.second->removeHealth(damage_);
				break;
			}
		}
	}
}

void Player::fireballAttack(const std::map<int, Enemy*>& enemies)
{
	if (mana_ < 12 || !getInventory()->hasItem(5)) return;
	mana_ -= 12;
	animState_ = spell;
	for (auto it : enemies)
	{
		if (getDistance(position_, it.second->getPosition()) <= 64)
		{
			it.second->removeHealth(2*damage_);
		}
	}
}

void Player::interact(const std::map<int, NPC*>& NPCs)
{
	for (auto it : NPCs)
	{
		if (getDistance(position_, it.second->getPosition()) <= 48)
		{
			if (dir_ == north && it.second->getPosition().y <= position_.y)
			{
				it.second->interact();
				break;
			}
			else if (dir_ == west && it.second->getPosition().x <= position_.x)
			{
				it.second->interact();
				break;
			}
			else if (dir_ == east && it.second->getPosition().x >= position_.x)
			{
				it.second->interact();
				break;
			}
			else if (dir_ == south && it.second->getPosition().y >= position_.y)
			{
				it.second->interact();
				break;
			}
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
	healthCounter_++;
	manaCounter_++;

	if(healthCounter_ % 15 == 0)
	{ 
		addHealth(level_);
		healthCounter_ = 0;
	}
	if (manaCounter_ % 5 == 0)
	{
		addMana(1);
		manaCounter_ = 0;
	}
	walking_ = false;
	if (gamePointer_->getApp()->getInput().isPressed('a'))
	{
		move(-2, 0);
	}
	if (gamePointer_->getApp()->getInput().isPressed('d'))
	{
		move(2, 0);
	}
	if (gamePointer_->getApp()->getInput().isPressed('s'))
	{
		move(0, 2);
	}
	if (gamePointer_->getApp()->getInput().isPressed('w'))
	{
		move(0, -2);
	}
	anim_.update(animState_, dir_, walking_);
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

