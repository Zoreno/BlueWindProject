#include "Tile.h"

Tile::Tile(sf::Texture& texture, bool walkable)
	: walkable_{ walkable }
{
	sprite_.setOrigin(sf::Vector2f(0.0f, 0.0f));
	sprite_.setTexture(texture);
}

void Tile::render(GameWindow & window, int x, int y)
{
	sprite_.setPosition(16 * x, 16 * y);
	window.draw(sprite_);
}
