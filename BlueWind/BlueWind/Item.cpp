#include "Item.h"
#include "GameWindow.h"

Item::Item(int ID, std::string name, sf::Texture& texture)
	: ID_{ID}, 
	name_{name}
{
	sprite_.setOrigin(sf::Vector2f(0.0f, 0.0f));
	sprite_.setTexture(texture);
	sprite_.setScale(sf::Vector2f(1.5f, 1.5f));
}

std::string Item::getName()
{
	return name_;
}

int Item::getID()
{
	return ID_;
}

const sf::Sprite& Item::getSprite() const
{
	return sprite_;
}

void Item::render(GameWindow & window, sf::Vector2f pos)
{
	sprite_.setPosition(pos);
	window.draw(sprite_);
}
