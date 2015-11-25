#include "Item.h"

Item::Item(int ID, std::string name, sf::Texture texture)
	: ID_{ID}, name_{name}
{
	sprite_.setOrigin(sf::Vector2f(0.0f, 0.0f));
	sprite_.setTexture(texture);
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
