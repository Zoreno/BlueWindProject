/*
* IDENTIFIERING
*
* Filnamn:    Entity.cpp
* Enhetsnamn: Entity
* Typ:        Definitioner hörande till klass Entity
* Revision:   1
* Skriven av: Olle Andersson, Jonas Ehn
*
*
* BESKRIVNING
*
* Denna implementeringsfil definierar medlemsfunktioner för klassen Entity.
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

#include "Entity.h"
#include "World.h"
#include "Universe.h"
#include "Game.h"
#include "Tile.h"
#include <math.h>
#include <algorithm>

using namespace std;

/*
* KONSTRUKTOR Entity(int level, int health, int damage, int ID,
*					 std::string name, sf::Vector2f position, World * worldPtr, sf::Texture& tex)
*
* BESKRIVNING
*
* Denna konstruktor konstruerar ett entity-objekt.
*
* INDATA
*
* level:		Nivå på entity-objektet
* health:		Antal hälsopoäng för objektet
* damage:		Antal skadepoäng för objektet
* ID:			Objektets ID-nummer
* name:			Objektets namn
* position:		Objektets position
* worldPtr:		En pekare till den värld som objektet ska finnas i
* tex:			Objektets textur
*
* UTDATA
*
* -
*
* SIDOEFFEKTER
*
* -
*
* UTNYTTJAR
*
* modul: sfml-grafik
* modul: std::string
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

Entity::Entity(int level, int health, int damage, int ID, std::string name, sf::Vector2f position, World * worldPtr, sf::Texture& tex)
	:level_{ level },
	health_{ health },
	maxHealth_{ health },
	damage_{ damage },
	ID_{ ID },
	name_{ name },
	position_{ position },
	worldPointer_{ worldPtr },
	anim_{ this, tex }
{}

/*
* FUNKTION move(float dx, float dy)
*
* BESKRIVNING
*
* Denna funktion flyttar ett entity-objekt en liten sträcka
*
* INDATA
*
* dx:		Förflyttningssträcka i x-riktning
* dy:		Förflyttningssträcka i y-riktning
*
* UTDATA
*
* -
*
* SIDOEFFEKTER
*
* -
*
* UTNYTTJAR
*
* modul: sfml-grafik
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

void Entity::move(float dx, float dy)
{
	sf::Vector2f upper_left = sf::Vector2f(position_) + sf::Vector2f(dx, dy);
	sf::Vector2f bottom_left = sf::Vector2f(position_.x, position_.y + Tile::TILESIZE - 1) + sf::Vector2f(dx, dy);
	sf::Vector2f upper_right = sf::Vector2f(position_.x + Tile::TILESIZE - 1, position_.y) + sf::Vector2f(dx, dy);
	sf::Vector2f bottom_right = sf::Vector2f(position_.x + Tile::TILESIZE - 1, position_.y + Tile::TILESIZE - 1) + sf::Vector2f(dx, dy);

	int mapWidth = worldPointer_->getMapWidth();
	int mapHeight = worldPointer_->getMapHeight();

	unsigned int cornerTopLeft = static_cast<unsigned int>(floor(upper_left.x / Tile::TILESIZE) + mapWidth*floor(upper_left.y / Tile::TILESIZE));
	unsigned int cornerTopRight = static_cast<unsigned int>(floor(bottom_left.x / Tile::TILESIZE) + mapWidth*floor(bottom_left.y / Tile::TILESIZE));
	unsigned int cornerBottomLeft = static_cast<unsigned int>(floor(upper_right.x / Tile::TILESIZE) + mapWidth*floor(upper_right.y / Tile::TILESIZE));
	unsigned int cornerBottomRight = static_cast<unsigned int>(floor(bottom_right.x / Tile::TILESIZE) + mapWidth*floor(bottom_right.y / Tile::TILESIZE));

	bool upper_left_walkable = worldPointer_->getUniverse()->getTile(worldPointer_->getTileVector().at(cornerTopLeft)).isWalkable();
	bool bottom_left_walkable = worldPointer_->getUniverse()->getTile(worldPointer_->getTileVector().at(cornerTopRight)).isWalkable();
	bool upper_right_walkable = worldPointer_->getUniverse()->getTile(worldPointer_->getTileVector().at(cornerBottomLeft)).isWalkable();
	bool bottom_right_walkable = worldPointer_->getUniverse()->getTile(worldPointer_->getTileVector().at(cornerBottomRight)).isWalkable();

	if (upper_left_walkable && bottom_left_walkable && upper_right_walkable && bottom_right_walkable)
		position_ += sf::Vector2f(dx, dy);

	if (dx < 0)
	{
		walking_ = true;
		dir_ = west;
	}
	else if (dx > 0)
	{
		walking_ = true;
		dir_ = east;
	}
	else if (dy > 0)
	{
		walking_ = true;
		dir_ = south;
	}
	else if (dy < 0)
	{
		walking_ = true;
		dir_ = north;
	}
}

/*
* FUNKTION teleport(float x, float y)
*
* BESKRIVNING
*
* Denna funktion teleporterar ett entity-objekt
*
* INDATA
*
* x:		x-koordinat att teleportera till
* y:		y-koordinat att teleportera till
*
* UTDATA
*
* -
*
* SIDOEFFEKTER
*
* -
*
* UTNYTTJAR
*
* modul: sfml-grafik
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

void Entity::teleport(float x, float y)
{
	position_ = sf::Vector2f(x, y);
}

/*
* FUNKTION getLevel() const
*
* BESKRIVNING
*
* Denna funktion returnerar objektets nivå
*
* INDATA
*
* -
*
* UTDATA
*
* int:		Ett tal med objektets nivå
*
* SIDOEFFEKTER
*
* -
*
* UTNYTTJAR
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

int Entity::getLevel() const
{
	return level_;
}

/*
* FUNKTION getHealth() const
*
* BESKRIVNING
*
* Denna funktion returnerar objektets hälsopoäng
*
* INDATA
*
* -
*
* UTDATA
*
* int:		Ett tal med objektets hälsopoäng
*
* SIDOEFFEKTER
*
* -
*
* UTNYTTJAR
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

int Entity::getHealth() const
{
	return health_;
}

/*
* FUNKTION getMaxHealth() const
*
* BESKRIVNING
*
* Denna funktion returnerar objektets maximala hälsopoäng
*
* INDATA
*
* -
*
* UTDATA
*
* int:		Ett tal med objektets maximala hälsopoäng
*
* SIDOEFFEKTER
*
* -
*
* UTNYTTJAR
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

int Entity::getMaxHealth() const
{
	return maxHealth_;
}

/*
* FUNKTION getDamage() const
*
* BESKRIVNING
*
* Denna funktion returnerar objektets skadeverkan
*
* INDATA
*
* -
*
* UTDATA
*
* int:		Ett tal med objektets skadeverkan
*
* SIDOEFFEKTER
*
* -
*
* UTNYTTJAR
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

int Entity::getDamage() const
{
	return damage_;
}

/*
* FUNKTION getID() const
*
* BESKRIVNING
*
* Denna funktion returnerar objektets ID
*
* INDATA
*
* -
*
* UTDATA
*
* int:		Ett tal med objektets ID
*
* SIDOEFFEKTER
*
* -
*
* UTNYTTJAR
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

int Entity::getID() const
{
	return ID_;
}

/*
* FUNKTION getName() const
*
* BESKRIVNING
*
* Denna funktion returnerar objektets namn
*
* INDATA
*
* -
*
* UTDATA
*
* std::string:		En sträng med objektets namn
*
* SIDOEFFEKTER
*
* -
*
* UTNYTTJAR
*
* modul: std::string
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

std::string Entity::getName() const
{
	return name_;
}

/*
* FUNKTION getPosition() const
*
* BESKRIVNING
*
* Denna funktion returnerar objektets position
*
* INDATA
*
* -
*
* UTDATA
*
* const sf::Vector2f:		En vektor med objektets position
*
* SIDOEFFEKTER
*
* -
*
* UTNYTTJAR
*
* modul: sfml-grafik
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

const sf::Vector2f Entity::getPosition() const
{
	return position_;
}

/*
* FUNKTION getWorld() const
*
* BESKRIVNING
*
* Denna funktion returnerar en pekare till världen som objektet
* befinner sig i.
*
* INDATA
*
* -
*
* UTDATA
*
* World*:		En pekare till världen som objektet befinner sig i
*
* SIDOEFFEKTER
*
* -
*
* UTNYTTJAR
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

World * Entity::getWorld() const
{
	return worldPointer_;
}

/*
* FUNKTION setCurrentWorld(World * worldPtr)
*
* BESKRIVNING
*
* Denna funktion sätter en nuvarande värld.
*
* INDATA
*
* worldPtr:		En pekare till en värld
*
* UTDATA
*
* -
*
* SIDOEFFEKTER
*
* -
*
* UTNYTTJAR
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

void Entity::setCurrentWorld(World * worldPtr)
{
	worldPointer_ = worldPtr;
}

/*
* FUNKTION addHealth(int value)
*
* BESKRIVNING
*
* Denna funktion lägger till hälsopoäng till objektet
*
* INDATA
*
* value:		Antalet hälsopoäng som ska läggas till
*
* UTDATA
*
* -
*
* SIDOEFFEKTER
*
* -
*
* UTNYTTJAR
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

void Entity::addHealth(int value)
{
	health_ = min(health_ + value, maxHealth_);
}

/*
* FUNKTION removeHealth(int value)
*
* BESKRIVNING
*
* Denna funktion tar bort hälsopoäng från objektet
*
* INDATA
*
* value:		Antalet hälsopoäng som ska tas bort
*
* UTDATA
*
* -
*
* SIDOEFFEKTER
*
* -
*
* UTNYTTJAR
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

void Entity::removeHealth(int value)
{
	health_ -= value;
	if (health_ <= 0)
	{
		health_ = 0;
		die();
	}
}

/*
* FUNKTION die()
*
* BESKRIVNING
*
* Denna funktion "dödar" ett objekt.
*
* INDATA
*
* -
*
* UTDATA
*
* -
*
* SIDOEFFEKTER
*
* -
*
* UTNYTTJAR
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

void Entity::die()
{
}