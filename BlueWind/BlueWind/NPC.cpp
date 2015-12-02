#include "NPC.h"
#include "World.h"
#include "Universe.h"
#include "Game.h"
#include <iostream>

using namespace std;

NPC::NPC(int level, int health, int damage, int ID, std::string name, sf::Vector2f position, World * worldPtr, sf::Texture& texture, string conversation, std::function<void(NPC*)> callbackFunc)
	: Entity(level, health, damage, ID, name, position, worldPtr, texture), 
	conversation_{ conversation }, 
	callback_{ callbackFunc }
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
	sprite_.setPosition(position_);
	window.draw(sprite_);
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
		callback_(this);
		// talkedTo = true; //TODO ta bort? kan kolla om player redan har föremål
	}
}

void NPC::die()
{
	worldPointer_->removeNPC(this);
}
