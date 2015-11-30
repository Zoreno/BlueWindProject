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

using namespace std;


Player::Player(World * worldPtr, sf::Texture& texture, Game* game, const string& fileName)
	: Entity(1, 100, 10, 0, "Kalle", sf::Vector2f(2 * 32, 2 * 32), worldPtr, fileName),
	mana_{ 20 }, maxMana_{ 20 }, gamePointer_{ game }, inventory_{ this,game }//, anim_{ this }
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
	//TODO jonas fixar.
	mana_ += value;
	if(mana_ > maxMana_)
	{
		mana_ = maxMana_;
	}
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


void Player::attack(const map<int, Enemy*> enemies)
{
	if (mana_ < 5) return;
	mana_ -= 5;
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
	return std::floor( 100 * std::pow(1.15f, level_));
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
	//anim_.state_ = anim_.idle;
	if (worldPointer_->getUniverse()->getGame()->getApp()->getInput().pressedButtons_.at('a'))
	{
		move(-1, 0);
		//anim_.state_ = anim_.walking;
		//anim_.dir_ = anim_.west;
	}
	if (worldPointer_->getUniverse()->getGame()->getApp()->getInput().pressedButtons_.at('d'))
	{
		move(1, 0);
		//anim_.state_ = anim_.walking;
		//anim_.dir_ = anim_.east;
	}
	if (worldPointer_->getUniverse()->getGame()->getApp()->getInput().pressedButtons_.at('s'))
	{
		move(0, 1);
		//anim_.state_ = anim_.walking;
		//anim_.dir_ = anim_.south;
	}
	if (worldPointer_->getUniverse()->getGame()->getApp()->getInput().pressedButtons_.at('w'))
	{
		move(0, -1);
		//anim_.state_ = anim_.walking;
		//anim_.dir_ = anim_.north;
	}

	//TODO balansera lite
	//addHealth(1);
	addMana(1);


	//anim_.update();

	checkSensors();
}

void Player::render(GameWindow & window)
{
	anim_.render(window);
}


void Player::die()
{
	gamePointer_->getApp()->setNextFrame(new GameOver(gamePointer_->getApp())); 
	//gamePointer_->getApp()->setZoomLevel(2.5f);
}


void Player::checkSensors()
{
	for (auto it : worldPointer_->getUniverse()->getCurrentWorld()->getSensorVector())
	{
		if (getDistance(position_, it.second->getPosition()) <= 32)
		{
			it.second->trigger();
			break;
		}
	}
}

