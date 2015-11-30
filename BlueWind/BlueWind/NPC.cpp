#include "NPC.h"
#include "World.h"
#include "Universe.h"
#include "Game.h"
#include <iostream>

using namespace std;

NPC::NPC(int level, int health, int damage, int ID, std::string name, sf::Vector2f position, World * worldPtr, sf::Texture& texture, string conversation, std::function<void(World*)> callbackFunc)
	: Entity(level, health, damage, ID, name, position, worldPtr, texture), conversation_{ conversation }, callback_{ callbackFunc }
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
	//window.draw(sprite_);
	anim_.render(window);
}

void NPC::talk() const
{
	worldPointer_->getUniverse()->getGame()->getUserInterface()->addStringToChatBox(conversation_);
}

void NPC::interact()
{
	talk();
	
	if (!talkedTo)
	{
		callback_(worldPointer_);
		//talkedTo = true;
	}
}

void NPC::die()
{
}
