/*
* IDENTIFIERING
*
* Filnamn:    Inventory.h
* Enhetsnamn: Inventory
* Typ:        Moduldeklaration
* Revision:   1
* Skriven av: Joakim Bertils, Johannes Grundell
*
*
* BESKRIVNING
*
* Denna modul representerar förråd i spelet.
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
#include <vector>
#include <stdexcept>
#include "Item.h"

/*
* Framåtdeklarationer
*/

class Player;
class Game;

/*
* KLASS InvetoryException
*
* BASKLASSER
*
* logic_error
*
* BESKRIVNING
*
* Klassen hanterar undantag i Inventory.
*
* TILLSTÅND
*
* -
*
* KONSTRUKTORER
*
* default-konstruktor.
*
* OPERATIONER
*
* -
*
* DATAMEDLEMMAR
*
* -
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151120  Ursprungsversion
*
*/

class InventoryException : public std::logic_error
{
public:
	using std::logic_error::logic_error;
};

/*
* KLASS Inventory
*
* BASKLASSER
*
* -
*
* BESKRIVNING
*
* Klassen representerar förråd i spelet
*
* TILLSTÅND
*
* -
*
* KONSTRUKTORER
*
* Inventory(Player* playerPtr, Game* gamePtr);
*
* OPERATIONER
*
* -
*
* DATAMEDLEMMAR
*
* items_:			Lista över förrådets föremål.
* maxSize_:			Förrådets maxstorlek.
* playerPointer_:	Pekare till spelaren.
* gamePointer_:		Pekare till spelframe.
* allItems_:		Lista med alla items som finns i spelet.
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151120  Ursprungsversion
*
*/

class Inventory
{
public:
	Inventory() = delete;
	Inventory(const Inventory&) = delete;
	Inventory& operator=(const Inventory&) = delete;
	Inventory(Player*, Game*);
	~Inventory();

	void addItem(int);
	void removeItem(int);
	bool hasItem(int);
	bool isFull();
	const int getCount(int);
	const int getSize();
	const unsigned int getMaxSize();

	Item* at(int);

	std::string toString();

private:
	std::vector<Item*> items_;
	const unsigned int maxSize_{8};
	Player* playerPointer_;
	Game* gamePointer_;

	void populateItemList();
	std::vector<Item*> allItems_;
};//class Inventory

/*
 * SLUT PÅ FILEN Inventory.h
 */