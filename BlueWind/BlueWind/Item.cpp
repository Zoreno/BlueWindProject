/*
* IDENTIFIERING
*
* Filnamn:    Item.cpp
* Enhetsnamn: Item
* Typ:        Definitioner hörande till klass Item
* Revision:   1
* Skriven av: Joakim Bertils, Johannes Grundell
*
*
* BESKRIVNING
*
* Denna implementeringsfil definierar medlemsfunktioner för klassen Item.
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

#include "Item.h"
#include "GameWindow.h"

using namespace std;

/*
* KONSTRUKTOR Item(int ID, string name, sf::Texture& texture)
*
* BESKRIVNING
*
* Denna konstruktor konstruerar ett föremål.
*
* INDATA
*
* ID:		Föremålets ID.
* name:		Föremålets namn.
* texture:	Textur för föremålet.
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
* modul: std::string
* modul: sfml-grafik
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

Item::Item(int ID, string name, sf::Texture& texture)
	:	ID_{ID}, 
		name_{name}
{
	sprite_.setOrigin(sf::Vector2f(0.0f, 0.0f));
	sprite_.setTexture(texture);
	sprite_.setScale(sf::Vector2f(1.5f, 1.5f));
}

/*
* FUNKTION Item::getName()
*
* BESKRIVNING
*
* Hämtar namn på föremålet.
*
* INDATA
*
* -
*
* UTDATA
*
* string: Föremålets namn
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

const string& Item::getName()
{
	return name_;
}

/*
* FUNKTION Item::getID()
*
* BESKRIVNING
*
* Hämtar ID på föremålet.
*
* INDATA
*
* -
*
* UTDATA
*
* int: Föremålets ID.
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

const int Item::getID()
{
	return ID_;
}

/*
* FUNKTION Item::getSprite()
*
* BESKRIVNING
*
* Hämtar textur för föremålet.
*
* INDATA
*
* 
*
* UTDATA
*
* sf::Sprite&: Föremålets textur.
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

const sf::Sprite& Item::getSprite() const
{
	return sprite_;
}

/*
* FUNKTION Item::render(GameWindow & window, sf::Vector2f pos)
*
* BESKRIVNING
*
* Renderar föremålet.
*
* INDATA
*
* window:	Fönstet som föremålet renderas i.
* pos:		Position som föremålet renderas på.
*
* UTDATA
*
* 
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

void Item::render(GameWindow & window, sf::Vector2f pos)
{
	sprite_.setPosition(pos);
	window.draw(sprite_);
}

/*
* SLUT PÅ FILEN Item.cpp
*/