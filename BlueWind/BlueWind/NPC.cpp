#include "NPC.h"
#include "World.h"
#include "Universe.h"
#include "Game.h"
#include <iostream>

using namespace std;

NPC::NPC(int level, int health, int damage, int ID, std::string name, sf::Vector2f position, World * worldPtr, sf::Texture& texture, string conversation)
	: Entity(level, health, damage, ID, name, position, worldPtr), conversation_{conversation}
{
	sprite_.setOrigin(sf::Vector2f(0.0f, 0.0f));
	sprite_.setPosition(position);
	sprite_.setTexture(texture);
}

void NPC::update()
{
}

void NPC::render(GameWindow & window)
{
	window.draw(sprite_);
}

void NPC::talk() const
{
	cout << conversation_ << endl;
}
