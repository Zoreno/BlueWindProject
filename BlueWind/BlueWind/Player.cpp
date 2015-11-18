#include "Player.h"

Player::Player(World * worldPtr, sf::Texture& texture)
	: Entity(1,100,10,0,"Kalle",sf::Vector2f(5*16,5*16), worldPtr)
{
	sprite_.setOrigin(sf::Vector2f(0.0f, 0.0f));
	sprite_.setTexture(texture);
}

int Player::getExperience() const
{
	return experience_;
}

void Player::addExperience(int value)
{
	experience_ += value;
}

void Player::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		move(0, -1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		move(-1, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		move(0, 1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		move(1, 0);
	}
}

void Player::render(GameWindow & window)
{
	sprite_.setPosition(position_);
	window.draw(sprite_);
}
