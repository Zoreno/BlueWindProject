/*
* IDENTIFIERING
*
* Filnamn:    World.h
* Enhetsnamn: World
* Typ:        Moduldeklaration
* Revision:   1
* Skriven av: Joakim Bertils, Johannes Grundell TODO Fler?
*
*
* BESKRIVNING
*
* Denna modul representerar en spelvärld.
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
#include <map>
#include <stdexcept>
#include "GameWindow.h"
#include "Enemy.h"
#include "NPC.h"
#include "Sensor.h"

/*
* Framåtdeklarationer
*/

class Universe;

/*
* KLASS WorldException
*
* BASKLASSER
*
* std::logic_error
*
* BESKRIVNING
*
* Klassen kastar undantag i World.
*
* TILLSTÅND
*
* -
*
* KONSTRUKTORER
*
* Ärver från std::logic_error.
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

class WorldException : public std::logic_error
{
public:
	using std::logic_error::logic_error;
};

/*
* KLASS World
*
* BASKLASSER
*
* -
*
* BESKRIVNING
*
* Klassen representerar en spelvärld.
*
* TILLSTÅND
*
* -
*
* KONSTRUKTORER
*
* World(int, Universe*, std::string, std::string)
*
* OPERATIONER
*
* -
*
* DATAMEDLEMMAR
*
* tileVector_:			Lista över spelvärldens tiles.
* ID_:					Spelvärldens ID.
* universePointer_:		Pekare till speluniversum.
* music_:				Musiken som spelas i spelvärlden.
* enemyVector_:			Lista över alla fiender i spelvärlden.
* removeEnemyVector_:	Lista över de fiender i spelvärlden som skall tas bort.
* NPCVector_:			Lista över alla NPC:er i spelvärlden.
* removeNPCVector_:		Lista över de NPC:er i spelvärlden som skall tas bort.
* sensorVector_:		Lista över alla sensorer i spelvärlden.
* removeSensorVector_:	Lista över de sensorer i spelvärlden som skall tas bort.
* mapWidth_:			Spelvärldens bredd (i antal tiles).
* mapHeight_:			Spelvärldens höjd (i antal tiles).
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151214  Ursprungsversion
*
*/

class World
{
public:
	World(int, Universe*, std::string, std::string);
	World() = delete;
	World(const World&) = delete;
	World& operator=(const World&) = delete;
	~World();

	void update();
	void render(GameWindow&);

	void loadWorld(std::string);
	void addEnemy(Enemy*);
	void addNPC(NPC*);
	void addSensor(Sensor*);
	void removeEnemy(Enemy*);
	void removeNPC(NPC*);
	void removeSensor(Sensor*);
	void changeTile(int, int);

	Universe* getUniverse() const;

	const int getID() const;
	const std::string getMusic();
	const int getMapWidth() const;
	const int getMapHeight() const;
	const std::vector<int> getTileVector() const;
	const std::map<int, Enemy*> getEnemyVector() const;
	const std::map<int, NPC*> getNPCVector() const;
	const std::map<int, Sensor*> getSensorVector() const;
private:
	std::vector<int> tileVector_;
	const int ID_;
	Universe* universePointer_;
	std::string music_;

	std::map<int, Enemy*> enemyVector_;
	std::vector<int> removeEnemyVector_;
	std::map<int, NPC*> NPCVector_;
	std::vector<int> removeNPCVector_;
	std::map<int, Sensor*> sensorVector_;
	std::vector<int> removeSensorVector_;

	int mapWidth_;
	int mapHeight_;

	int getIntFromColor(sf::Color);

	void updateLists();
}; // class World

/*
* SLUT PÅ FILEN World.h
*/