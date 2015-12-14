/*
* IDENTIFIERING
*
* Filnamn:    Item.h
* Enhetsnamn: Item
* Typ:        Moduldeklaration
* Revision:   1
* Skriven av: Joakim Bertils, Johannes Grundell
*
*
* BESKRIVNING
*
* Denna modul representerar föremål i spelet.
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151120  Ursprungsversion
*
*/

#pragma once

/*
* REFERERADE BIBLIOTEK OCH MODULER
*/

#include "GameWindow.h"
#include <string>
#include <SFML\Graphics.hpp>

/*
* KLASS Item
*
* BASKLASSER
*
* -
*
* BESKRIVNING
*
* Klassen representerar föremål i spelet
*
* TILLSTÅND
*
* -
*
* KONSTRUKTORER
*
* Item(int, std::string name, sf::Texture& texture);
*
* OPERATIONER
*
* -
*
* DATAMEDLEMMAR
*
* name_:	Anger namnet på föremålet.
* ID_:		Anger föremålets ID.
* sprite_:	Spriten som används som ikon för föremålet.
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151120  Ursprungsversion
*
*/

class Item
{
public:
	Item(int, std::string, sf::Texture&);
	Item() = delete;
	Item(const Item&) = delete;
	Item& operator=(const Item&) = delete;

	const std::string& getName();
	const int getID();
	const sf::Sprite& getSprite() const;

	void render(GameWindow&, sf::Vector2f);

private:
	std::string name_;
	int ID_;
	sf::Sprite sprite_;
};//class Item

/*
  * SLUT PÅ FILEN Item.h
	  */