/*
* IDENTIFIERING
*
* Filnamn:    Tile.cpp
* Enhetsnamn: Tile
* Typ:        Definitioner hörande till klassen Tile
* Revision:   1
* Skriven av: Joakim Bertils, Johannes Grundell
*
*
* BESKRIVNING
*
* Denna implementeringsfil definierar medlemsfunktioner för klassen Tile.
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151214  Ursprungsversion
*/

/*
* REFERERADE BIBLIOTEK OCH MODULER
*/

#include "Tile.h"

/*
* KONSTRUKTOR Tile::Tile(sf::Texture& texture, bool walkable)
*
* BESKRIVNING
*
* Denna konstruktor skapar en ruta (tile).
*
* INDATA
*
* texture: Rutans textur.
* walkable: Anger om man ska kunna gå på rutan (true) eller ej.
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
* 1                    151214          Ursprungsversion
*
*/

Tile::Tile(sf::Texture& texture, bool walkable)
	: walkable_{ walkable }
{
	sprite_.setOrigin(sf::Vector2f(0.0f, 0.0f));
	sprite_.setTexture(texture);
}

/*
* FUNKTION Tile::render(GameWindow& window, int x, int y)
*
* BESKRIVNING
*
* Ritar upp rutan.
*
* INDATA
*
* window:	Fönster som rutan ska ritas upp i.
* x:		x-positionen där rutan ska ritas.
* y:		y-positionen där rutan ska ritas.
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
* 1                    151214          Ursprungsversion
*
*/

void Tile::render(GameWindow& window, int x, int y)
{
	sprite_.setPosition(static_cast<float>(TILESIZE * x), static_cast<float>(TILESIZE * y));
	window.draw(sprite_);
}

/*
* FUNKTION Tile::isWalkable()
*
* BESKRIVNING
*
* Hämtar om man kan gå på rutan eller ej.
*
* INDATA
*
* -
*
* UTDATA
*
* bool: Anger om man kan gå på rutan (true) eller ej.
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
* 1                    151214          Ursprungsversion
*
*/

bool Tile::isWalkable()
{
	return walkable_;
}

/*
* SLUT PÅ FILEN Tile.cpp
*/