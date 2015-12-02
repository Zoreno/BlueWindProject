#include "Animation.h"
#include "Entity.h"
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;

Animation::Animation(Entity* entityPointer, sf::Texture& tex)
	: entityPtr_{entityPointer}, 
	texture_{tex}
{
	currentSprite_.setTexture(tex);
}

void Animation::update(int state, int dir, bool walking)
{
	animState = state;
	if (state == Entity::STATES::attacking)
	{
		if (attackCounter % 15 == 14)
		{
			entityPtr_->animState_ = Entity::STATES::walking1;
			attackCounter = 0;
		}
		attackCounter++;
		return;
	}
	if (walking && (counter % 20) == 0)
	{
		switch (state)
		{
		case Entity::STATES::walking1:
			entityPtr_->animState_ = Entity::STATES::walking2;
			break;
		case Entity::STATES::walking2:
			entityPtr_->animState_ = Entity::STATES::walking1;
			break;
		case Entity::STATES::attacking:
			break;
		}
	}
	counter++;
}

void Animation::render(GameWindow& window)
{
	sf::Rect<int> rect(32 * (animState + 3 * entityPtr_->dir_), 0, 32, 32);
	currentSprite_.setTextureRect(rect);
	currentSprite_.setPosition(entityPtr_->getPosition());
	window.draw(currentSprite_);
}
