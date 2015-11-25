#include "Player.h"
#include "World.h"
#include "Universe.h"
#include "Game.h"
#include "Frame.h"
#include "Application.h"
#include "Input.h"
#include <map>

using namespace std;


Player::Player(World * worldPtr, sf::Texture& texture, Game* game)
	: Entity(1, 100, 10, 0, "Kalle", sf::Vector2f(2 * 16, 2 * 16), worldPtr),
	mana_{ 20 }, maxMana_{ 20 }, maxExperience_{ 100 }, gamePointer_{ game }, inventory_{ this,game }, anim_{ this }
{
	inventory_.addItem(0);
}

int Player::getExperience() const
{
	return experience_;
}

void Player::addExperience(int value)
{
	experience_ += value;
}

int Player::getMana() const
{
	return mana_;
}

void Player::setMana(int value)
{
	mana_ = value;
}

int Player::getMaxMana() const
{
	return maxMana_;
}

void Player::setMaxMana(int value)
{
	maxMana_ = value;
}

int Player::getMaxExperience()
{
	return maxExperience_;
}

Inventory* Player::getInventory()
{
	return &inventory_;
}

void Player::update()
{
	anim_.state_ = anim_.idle;
	//bool isIdle_ {true};
	if (worldPointer_->getUniverse()->getGame()->getApp()->getInput().pressedButtons_.at('a'))
	{
		move(-1, 0);
		anim_.state_ = anim_.walking;
		anim_.dir_ = anim_.west;
		//isIdle_ = false;
	}
	if (worldPointer_->getUniverse()->getGame()->getApp()->getInput().pressedButtons_.at('d'))
	{
		move(1, 0);
		anim_.state_ = anim_.walking;
		anim_.dir_ = anim_.east;
		//isIdle_ = false;
	}
	if (worldPointer_->getUniverse()->getGame()->getApp()->getInput().pressedButtons_.at('s'))
	{
		move(0, 1);
		anim_.state_ = anim_.walking;
		anim_.dir_ = anim_.south;
		//isIdle_ = false;
	}
	if (worldPointer_->getUniverse()->getGame()->getApp()->getInput().pressedButtons_.at('w'))
	{
		move(0, -1);
		anim_.state_ = anim_.walking;
		anim_.dir_ = anim_.north;
		//isIdle_ = false;
	}
	//if (isIdle_)
		//anim_.state_ = anim_.idle;
	anim_.update();
			}

void Player::render(GameWindow & window)
{
	//sprite_.setPosition(position_);
	//window.draw(sprite_);
	anim_.render(window);
}

const int Player::getAttackCooldown() const
{
	return attackCooldown_;
}

