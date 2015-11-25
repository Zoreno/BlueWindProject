#pragma once

#include <string>
#include "GameWindow.h"
#include <SFML\Graphics.hpp>

class Item
{
public:
	Item(int, std::string, sf::Texture&);
	Item() = delete;
	Item(const Item&) = delete;
	Item& operator=(const Item&) = delete;

	std::string getName();
	int getID();
	const sf::Sprite& getSprite() const;

	void render(GameWindow&, sf::Vector2f);

private:
	std::string name_;
	int ID_;
	sf::Sprite sprite_;

};