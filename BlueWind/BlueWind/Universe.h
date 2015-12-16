/* IDENTIFIERING
*
* Filnamn:    Universe.h
* Enhetsnamn: Universe
* Typ:        Moduldeklaration
* Revision:   1
* Skriven av: Simon Arkeholt, Fredrik Gustafsson, Jonas Ehn, Olle Andersson, Joakim Bertils, Johannes Grundell
*
*
* BESKRIVNING
*
* Denna modul representerar speluniversumet och dess beståndsdelar.
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

#include <map>
#include <stdexcept>
#include "GameWindow.h"
#include "World.h"
#include "Tile.h"
#include "Enemy.h"
#include "NPC.h"
#include "Sensor.h"

class Game;

/*
* KLASS UniverseException
*
* BASKLASSER
*
* logic_error
*
* BESKRIVNING
*
* Klassen kastar undantag för Universe.
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
* 1            151214  Ursprungsversion
*
*/
class UniverseException : public std::logic_error
{
public:
	using std::logic_error::logic_error;
};

/*
* KLASS Universe
*
* BASKLASSER
*
* -
*
* BESKRIVNING
*
* Klassen representerar speluniversumet. Universe skapar och håller reda på alla världar i spelet.
*
* TILLSTÅND
*
* -
*
* KONSTRUKTORER
*
* Universe(Game*)
*
* OPERATIONER
*
* -
*
* DATAMEDLEMMAR
*
* gamePointer_:		Pekare till aktuellt Game.
* currentWorld_:	Pekare till världen spelaren befinner sig i.
* worlds_:			Vektor innehållande spelets alla världar.	
* tileAtlas_:		Map innehållande pekare till alla Tiles och respektive nyckel.
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151214  Ursprungsversion
*
*/

class Universe
{
public:
	Universe(Game*);
	Universe(const Universe&) = delete;
	Universe& operator=(const Universe&) = delete;

	~Universe();

	void update();
	void render(GameWindow&);
	World* getCurrentWorld();
	World* getWorld(int);
	void setCurrentWorld(int);

	void switchWorld(int, int, int);

	Tile& getTile(int);

	Game* getGame() const;

	void addEnemy(int, Enemy*);
	void addNPC(int, NPC*);
	void addSensor(int, Sensor*);

	void populateCity();

private:
	Game* gamePointer_;
	World* currentWorld_;
	std::vector<World*> worlds_;
	std::map<int, Tile*> tileAtlas_;

	void loadTiles();
	void loadWorlds();
	void populateWorlds();	
}; //class NPC

   /*
   * SLUT PÅ FILEN NPC.h
   */