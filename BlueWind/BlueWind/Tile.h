/*
* IDENTIFIERING
*
* Filnamn:    Tile.h
* Enhetsnamn: Tile
* Typ:        Moduldeklaration
* Revision:   1
* Skriven av: Joakim Bertils, Johannes Grundell
*
*
* BESKRIVNING
*
* Denna modul representerar en ruta (tile) i spelvärlden.
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151214  Ursprungsversion
*
*/

#pragma once

/*
* REFERERADE BIBLIOTEK OCH MODULER
*/

#include <string>
#include <SFML\Graphics.hpp>
#include "GameWindow.h"

/*
* KLASS Tile
*
* BASKLASSER
*
* -
*
* BESKRIVNING
*
* Klassen representerar en ruta (tile) i spelvärlden.
*
* KONSTRUKTORER
*
* Tile(sf::Texture&, bool)
*
* DATAMEDLEMMAR
*
* sprite_:		Den bild som ritas upp på rutan.
* walkable_:	Anger om man kan gå på rutan eller ej.
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151214  Ursprungsversion
*
*/

class Tile
{
public:
	Tile(sf::Texture&, bool);
	Tile() = delete;
	Tile(Tile&) = delete;
	Tile& operator=(const Tile&) = delete;

	void render(GameWindow&, int, int);

	static const int TILESIZE{ 32 };

	bool isWalkable();
private:
	sf::Sprite sprite_;
	bool walkable_;
};

/*
* SLUT PÅ FILEN Tile.h
*/