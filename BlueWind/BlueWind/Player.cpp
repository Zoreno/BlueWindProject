/*
* IDENTIFIERING
*
* Filnamn:    Player.cpp
* Enhetsnamn: Player
* Typ:        Definitioner hörande till klass Player
* Revision:   1
* Skriven av: Jonas Ehn, Olle Andersson
*
*
* BESKRIVNING
*
* Denna implementeringsfil definierar medlemsfunktioner för klassen Player.
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151120  Ursprungsversion
*/

/*
* REFERERADE BIBLIOTEK OCH MODULER
*/

#include <map>
#include <math.h>
#include <algorithm>

#include "Player.h"
#include "World.h"
#include "Universe.h"
#include "Game.h"
#include "Frame.h"
#include "Application.h"
#include "Input.h"
#include "GameOver.h"

using namespace std;
/*
* KONSTRUKTOR Player(World * worldPtr, sf::Texture& texture, Game* game)
*
* BESKRIVNING
*
* Denna konstruktor konstruerar spelaren
*
* INDATA
*
* worldPtr:		Pekare till den aktuella världen
* texture:		En referens till en texture
* game:			En pekare till Game
*
* UTDATA
*
* -
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

Player::Player(World * worldPtr, sf::Texture& texture, Game* game)
	: Entity(1, 300, 50, 0, "Faranos", sf::Vector2f(20 * 32, 20 * 32), worldPtr, game->getTexture("player")),
	mana_{ 60 },
	maxMana_{ mana_ },
	gamePointer_{ game },
	inventory_{ this,game }
{}

/*
* FUNKTION Player::getExperience() const
*
* BESKRIVNING
*
* Denna funktion returnerar erfarenhetspoängen som spelaren har
*
* INDATA
*
* -
*
* UTDATA
*
* int:		Erfarenhetspoäng
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/
int Player::getExperience() const
{
	return experience_;
}

/*
* FUNKTION Player::addExperience(int value)
*
* BESKRIVNING
*
* Denna funktion ökar spelarens erfarenhetspoäng
*
* INDATA
*
* value:	Ett heltal med erfarenhetspoäng att lägga till
*
* UTDATA
*
* -
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/
void Player::addExperience(int value)
{
	experience_ += value;
	while (checkForLevelup())
	{
		maxHealth_ += 50;
		health_ = maxHealth_;
		maxMana_ += 20;
		mana_ = maxMana_;
		damage_ += 30;
	}
}

/*
* FUNKTION Player::getMana() const
*
* BESKRIVNING
*
* Denna funktion returnerar spelarens magipoäng
*
* INDATA
*
* -
*
* UTDATA
*
* mana_:	Ett heltal med spelarens magipoäng
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/
int Player::getMana() const
{
	return mana_;
}

/*
* FUNKTION Player::setMana(int value)
*
* BESKRIVNING
*
* Denna funktion sätter spelarens magipoäng till ett visst värde
*
* INDATA
*
* value:	Ett heltal som spelarens magipoäng sätts till
*
* UTDATA
*
* -
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/
void Player::setMana(int value)
{
	mana_ = value;
}

/*
* FUNKTION Player::addMana(int value)
*
* BESKRIVNING
*
* Denna funktion lägger till magipoäng till spelaren
*
* INDATA
*
* value:	Ett heltal som spelarens magipoäng ökas med
*
* UTDATA
*
* -
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/
void Player::addMana(int value)
{
	mana_ = min(mana_ + value, maxMana_);
}

/*
* FUNKTION getMaxMana() const
*
* BESKRIVNING
*
* Denna funktion returnerar maxantalet magipoäng som spelaren har
*
* INDATA
*
* -
*
* UTDATA
*
* int:		Ett heltalsvärde som är spelarens maximala magipoäng
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/
int Player::getMaxMana() const
{
	return maxMana_;
}

/*
* FUNKTION setMaxMana(int value)
*
* BESKRIVNING
*
* Denna funktion sätter spelarens maximala antal magipoäng
*
* INDATA
*
* value:	Heltal som sätts till maximala antal magipoäng
*
* UTDATA
*
* -
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/
void Player::setMaxMana(int value)
{
	maxMana_ = value;
	mana_ = value;
}

/*
* FUNKTION getMaxExperience()
*
* BESKRIVNING
*
* Denna funktion returnerar spelarens maximala erfarenhetspoäng
*
* INDATA
*
* -
*
* UTDATA
*
* int:	Maximala antalet erfarenhetspoäng
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/
int Player::getMaxExperience()
{
	return getXpToLevel();
}

/*
* FUNKTION setName(std::string name)
*
* BESKRIVNING
*
* Denna funktion sätter spelarens namn
*
* INDATA
*
* -
*
* UTDATA
*
* -
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/
void Player::setName(std::string name)
{
	name_ = name;
}

/*
* FUNKTION setMaxHealth(int value)
*
* BESKRIVNING
*
* Denna funktion sätter spelarens maximala hälsopoäng
*
* INDATA
*
* value:	Heltalsvärde som blir spelarens maximala hälsopoäng
*
* UTDATA
*
* -
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/
void Player::setMaxHealth(int value)
{
	maxHealth_ = value;
	health_ = value;
}

/*
* FUNKTION setDamage(int value)
*
* BESKRIVNING
*
* Denna funktion sätter spelarens skadeverkan
*
* INDATA
*
* value:	Heltalsvärde som blir spelarens skadeverkan
*
* UTDATA
*
* -
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/
void Player::setDamage(int value)
{
	damage_ = value;
}

/*
* FUNKTION setLevel(int value)
*
* BESKRIVNING
*
* Denna funktion sätter spelarens nivå
*
* INDATA
*
* value:	Heltalsvärde som blir spelarens nivå
*
* UTDATA
*
* -
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/
void Player::setLevel(int value)
{
	level_ = value;
}

/*
* FUNKTION setExperience(int value)
*
* BESKRIVNING
*
* Denna funktion sätter spelarens erfarenhetspoäng
*
* INDATA
*
* value:	Heltalsvärde som blir spelarens erfarenhetspoäng
*
* UTDATA
*
* -
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/
void Player::setExperience(int value)
{
	experience_ = value;
}

/*
* FUNKTION getInventory()
*
* BESKRIVNING
*
* En funktion som returnerar en pekare till spelarens inventory
*
* INDATA
*
* -
*
* UTDATA
*
* Inventory* :		En pekare till spelarens inventory
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

Inventory* Player::getInventory()
{
	return &inventory_;
}

/*
* FUNKTION swordAttack(const map<int, Enemy*>& enemies)
*
* BESKRIVNING
*
* En funktion som representerar en svärdsattack
*
* INDATA
*
* enemies : en map med alla fiender i världen
*
* UTDATA
*
* -
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

void Player::swordAttack(const map<int, Enemy*>& enemies)
{
	if (mana_ < 4) return;
	mana_ -= 4;
	animState_ = attacking;
	for (auto it : enemies)
	{
		if (getDistance(position_, it.second->getPosition()) <= 32)
		{
			if (dir_ == north && it.second->getPosition().y <= position_.y)
			{
				it.second->removeHealth(damage_);
				break;
			}
			else if (dir_ == west && it.second->getPosition().x <= position_.x)
			{
				it.second->removeHealth(damage_);
				break;
			}
			else if (dir_ == east && it.second->getPosition().x >= position_.x)
			{
				it.second->removeHealth(damage_);
				break;
			}
			else if (dir_ == south && it.second->getPosition().y >= position_.y)
			{
				it.second->removeHealth(damage_);
				break;
			}
		}
	}
}

/*
* FUNKTION fireballAttack(const std::map<int, Enemy*>& enemies)
*
* BESKRIVNING
*
* En funktion som representerar en magiattack
*
* INDATA
*
* enemies : en map med alla fiender i världen
*
* UTDATA
*
* -
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

void Player::fireballAttack(const std::map<int, Enemy*>& enemies)
{
	if (mana_ < 12 || !getInventory()->hasItem(5)) return;
	mana_ -= 12;
	animState_ = spell;
	for (auto it : enemies)
	{
		if (getDistance(position_, it.second->getPosition()) <= 64)
		{
			it.second->removeHealth(2 * damage_);
		}
	}
}

/*
* FUNKTION interact(const std::map<int, NPC*>& NPCs)
*
* BESKRIVNING
*
* En funktion som representerar interaktion med NPC:er
*
* INDATA
*
* NPCs : en map med alla NPCer i världen
*
* UTDATA
*
* -
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

void Player::interact(const std::map<int, NPC*>& NPCs)
{
	for (auto it : NPCs)
	{
		if (getDistance(position_, it.second->getPosition()) <= 48)
		{
			if (dir_ == north && it.second->getPosition().y <= position_.y)
			{
				it.second->interact();
				break;
			}
			else if (dir_ == west && it.second->getPosition().x <= position_.x)
			{
				it.second->interact();
				break;
			}
			else if (dir_ == east && it.second->getPosition().x >= position_.x)
			{
				it.second->interact();
				break;
			}
			else if (dir_ == south && it.second->getPosition().y >= position_.y)
			{
				it.second->interact();
				break;
			}
		}
	}
}

/*
* FUNKTION getXpToLevel()
*
* BESKRIVNING
*
* En funktion som räknar ut hur många erfarenhetspoäng
* som krävs för att nå nästa nivå.
*
* INDATA
*
* -
*
* UTDATA
*
* int : antalet erfarenhetspoäng till nästa nivå
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

int Player::getXpToLevel()
{
	return static_cast<int>(std::floor(100 * std::pow(1.15f, level_)));
}

/*
* FUNKTION checkForLevelup()
*
* BESKRIVNING
*
* En funktion som räknar ut om spelaren går upp en nivå
*
* INDATA
*
* -
*
* UTDATA
*
* bool : ska spelaren gå upp en nivå?
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

bool Player::checkForLevelup()
{
	if (experience_ >= getXpToLevel())
	{
		experience_ -= getXpToLevel();
		level_++;
		return true;
	}
	return false;
}

/*
* FUNKTION update()
*
* BESKRIVNING
*
* En funktion som uppdaterar spelaren
*
* INDATA
*
* -
*
* UTDATA
*
* -
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

void Player::update()
{
	healthCounter_++;
	manaCounter_++;

	if (healthCounter_ % 15 == 0)
	{
		addHealth(level_);
		healthCounter_ = 0;
	}
	if (manaCounter_ % 5 == 0)
	{
		addMana(1);
		manaCounter_ = 0;
	}
	walking_ = false;
	if (gamePointer_->getApp()->getInput().isPressed('a'))
	{
		move(-2.0f, 0.0f);
	}
	if (gamePointer_->getApp()->getInput().isPressed('d'))
	{
		move(2.0f, 0.0f);
	}
	if (gamePointer_->getApp()->getInput().isPressed('s'))
	{
		move(0.0f, 2.0f);
	}
	if (gamePointer_->getApp()->getInput().isPressed('w'))
	{
		move(0.0f, -2.0f);
	}
	anim_.update(animState_, dir_, walking_);
	checkSensors();
}

/*
* FUNKTION render(GameWindow & window)
*
* BESKRIVNING
*
* En funktion som renderar spelaren
*
* INDATA
*
* window : spelfönstret som allt ritas upp i
*
* UTDATA
*
* -
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

void Player::render(GameWindow & window)
{
	anim_.render(window);
}

/*
* FUNKTION die()
*
* BESKRIVNING
*
* En funktion som dödar spelaren
*
* INDATA
*
* -
*
* UTDATA
*
* -
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

void Player::die()
{
	gamePointer_->getApp()->setNextFrame(new GameOver(gamePointer_->getApp()));
}

/*
* FUNKTION checkSensors()
*
* BESKRIVNING
*
* En funktion som kontrollerar om spelaren är nära nog för att trigga någon sensor
*
* INDATA
*
* -
*
* UTDATA
*
* -
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

void Player::checkSensors()
{
	for (auto it : worldPointer_->getSensorVector())
	{
		if (getDistance(position_, it.second->getPosition()) <= 32)
		{
			it.second->trigger();
			break;
		}
	}
}

/*
* Slut på filen Player.cpp
*/