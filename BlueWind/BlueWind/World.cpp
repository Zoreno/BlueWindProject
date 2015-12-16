/*
* IDENTIFIERING
*
* Filnamn:    World.cpp
* Enhetsnamn: World
* Typ:        Definitioner hörande till klassen World
* Revision:   1
* Skriven av: Joakim Bertils, Johannes Grundell
*
*
* BESKRIVNING
*
* Denna implementeringsfil definierar medlemsfunktioner för klassen World.
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

#include "World.h"
#include "Universe.h"

using namespace std;

/*
* KONSTRUKTOR World::World(int ID, Universe* universePtr, std::string mapFile, string music)
*
* BESKRIVNING
*
* Denna konstruktor skapar en spelvärld.
*
* INDATA
*
* ID:			Spelvärldens ID.
* universePtr:	Pekare till speluniversum.
* mapFile:		Fil som innehåller spelvärldens pixelkarta (hur världen ska se ut).
* music:		Musiken som ska spelas i spelvärlden.
*
* UTDATA
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

World::World(int ID, Universe* universePtr, std::string mapFile, string music)
	: ID_{ ID },
	universePointer_{ universePtr },
	music_{ music }
{
	loadWorld(mapFile);
}

/*
* DESTRUKTOR World::~World()
*
* BESKRIVNING
*
* Denna destruktor destruerar ett World-objekt
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

World::~World()
{
	universePointer_ = nullptr;

	while (!enemyVector_.empty())
	{
		auto it = enemyVector_.begin();
		delete it->second;
		enemyVector_.erase(it);
	}

	while (!NPCVector_.empty())
	{
		auto it = NPCVector_.begin();
		delete it->second;
		NPCVector_.erase(it);
	}

	while (!sensorVector_.empty())
	{
		auto it = sensorVector_.begin();
		delete it->second;
		sensorVector_.erase(it);
	}
}

/*
* FUNKTION World::update()
*
* BESKRIVNING
*
* Uppdaterar spelvärldens beståndsdelar.
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
* 1                    151214          Ursprungsversion
*
*/

void World::update()
{
	for (auto it : enemyVector_)
	{
		it.second->update();
	}
	updateLists();
}

/*
* FUNKTION World::render(GameWindow& window)
*
* BESKRIVNING
*
* Ritar upp tiles runt spelkaraktären, samt spelvärldens samtliga fiender och NPC:er.
*
* INDATA
*
* window: Fönster som spelvärlden ska ritas upp i.
*
* UTDATA
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

void World::render(GameWindow& window)
{
	sf::View view = window.getView();

	int startX = (static_cast<int>(view.getCenter().x) - (20 * Tile::TILESIZE)) / Tile::TILESIZE;
	int endX = (static_cast<int>(view.getCenter().x) + (20 * Tile::TILESIZE)) / Tile::TILESIZE;
	int startY = (static_cast<int>(view.getCenter().y) - (20 * Tile::TILESIZE)) / Tile::TILESIZE;
	int endY = (static_cast<int>(view.getCenter().y) + (20 * Tile::TILESIZE)) / Tile::TILESIZE;

	if (startX > mapWidth_)
		startX = mapWidth_;
	if (startX < 0)
		startX = 0;

	if (endX > mapWidth_)
		endX = mapWidth_;
	if (endX < 0)
		endX = 0;

	if (startY > mapHeight_)
		startY = mapHeight_;
	if (startY < 0)
		startY = 0;

	if (endY > mapHeight_)
		endY = mapHeight_;
	if (endY < 0)
		endY = 0;

	for (int y = startY; y < endY; ++y)
	{
		for (int x = startX; x < endX; ++x)
		{
			universePointer_->getTile(tileVector_.at(x + mapWidth_*y)).render(window, x, y);
		}
	}

	for (auto it : enemyVector_)
	{
		it.second->render(window);
	}

	for (auto it : NPCVector_)
	{
		it.second->render(window);
	}
}

/*
* FUNKTION World::loadWorld(std::string mapFile)
*
* BESKRIVNING
*
* Läser in och översätter spelvärldens pixelkarta till en lista med motsvarande tiles.
*
* INDATA
*
* mapFile: Spelvärldens pixelkarta.
*
* UTDATA
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

void World::loadWorld(std::string mapFile)
{
	sf::Image image;
	if (!image.loadFromFile(mapFile))
	{
		throw WorldException("Kunde inte läsa världsfil:" + mapFile);
	}

	mapWidth_ = image.getSize().x;
	mapHeight_ = image.getSize().y;

	for (int y{ 0 }; y < mapHeight_; ++y)
	{
		for (int x{ 0 }; x < mapWidth_; ++x)
		{
			tileVector_.push_back(getIntFromColor(image.getPixel(x, y)));
		}
	}
}

/*
* FUNKTION World::addEnemy(Enemy* enemyPtr)
*
* BESKRIVNING
*
* Lägger till en fiende i spelvärlden.
*
* INDATA
*
* enemyPtr: Pekare till den fiende som skall läggas till.
*
* UTDATA
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

void World::addEnemy(Enemy* enemyPtr)
{
	enemyVector_.emplace(enemyPtr->getID(), enemyPtr);
}

/*
* FUNKTION World::addNPC(NPC* NPCPtr)
*
* BESKRIVNING
*
* Lägger till en NPC i spelvärlden.
*
* INDATA
*
* NPCPtr: Pekare till den NPC som skall läggas till.
*
* UTDATA
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

void World::addNPC(NPC* NPCPtr)
{
	NPCVector_.emplace(NPCPtr->getID(), NPCPtr);
}

/*
* FUNKTION World::addSensor(Sensor* sensorPtr)
*
* BESKRIVNING
*
* Lägger till en sensor i spelvärlden.
*
* INDATA
*
* sensorPtr: Pekare till den sensor som skall läggas till.
*
* UTDATA
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

void World::addSensor(Sensor* sensorPtr)
{
	sensorVector_.emplace(sensorPtr->getID(), sensorPtr);
}

/*
* FUNKTION World::removeEnemy(Enemy* enemyPtr)
*
* BESKRIVNING
*
* Lägger till en fiende i "removeEnemyVector_" (listan över de fiender i spelvärlden som skall tas bort).
*
* INDATA
*
* enemyPtr: Pekare till den fiende som skall tas bort.
*
* UTDATA
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

void World::removeEnemy(Enemy* enemyPtr)
{
	removeEnemyVector_.push_back(enemyPtr->getID());
}

/*
* FUNKTION World::removeNPC(NPC* NPCPtr)
*
* BESKRIVNING
*
* Lägger till en NPC i "removeNPCVector_" (listan över de NPC:er i spelvärlden som skall tas bort).
*
* INDATA
*
* NPCPtr: Pekare till den NPC som skall tas bort.
*
* UTDATA
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

void World::removeNPC(NPC* NPCPtr)
{
	removeNPCVector_.push_back(NPCPtr->getID());
}

/*
* FUNKTION World::removeSensor(Sensor* sensorPtr)
*
* BESKRIVNING
*
* Lägger till en sensor i "removeSensorVector_" (listan över de sensorer i spelvärlden som skall tas bort).
*
* INDATA
*
* sensorPtr: Pekare till den sensor som skall tas bort.
*
* UTDATA
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

void World::removeSensor(Sensor* sensorPtr)
{
	removeSensorVector_.push_back(sensorPtr->getID());
}

/*
* FUNKTION World::changeTile(int pos, int value)
*
* BESKRIVNING
*
* Ersätter en tile i spelvärlden med en annan typ av tile.
*
* INDATA
*
* pos: Positionen för den tile som skall ersättas.
* value: Den typ av tile som den gamla ska ersättas med.
*
* UTDATA
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

void World::changeTile(int pos, int value)
{
	if (pos < 0 || (static_cast<unsigned int>(pos) > tileVector_.size()))
	{
		throw WorldException("Åtkomst till tile utanför kartan, du angav:" + pos);
	}

	tileVector_.at(pos) = value;
}

/*
* FUNKTION World::getUniverse()
*
* BESKRIVNING
*
* Hämtar (en pekare till) det speluniversum som spelvärlden tillhör.
*
* INDATA
*
* -
*
* UTDATA
*
* Universe*: Pekare till det speluniversum som spelvärlden tillhör.
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151214          Ursprungsversion
*
*/

Universe* World::getUniverse() const
{
	return universePointer_;
}

/*
* FUNKTION World::getID()
*
* BESKRIVNING
*
* Hämtar spelvärldens ID.
*
* INDATA
*
* -
*
* UTDATA
*
* const int: Spelvärldens ID.
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151214          Ursprungsversion
*
*/

const int World::getID() const
{
	return ID_;
}

/*
* FUNKTION World::getMusic()
*
* BESKRIVNING
*
* Hämtar musiken som spelas i spelvärlden.
*
* INDATA
*
* -
*
* UTDATA
*
* std::string: Den musik som spelas i spelvärlden.
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151214          Ursprungsversion
*
*/

const std::string World::getMusic()
{
	return music_;
}

/*
* FUNKTION World::getMapWidth()
*
* BESKRIVNING
*
* Hämtar spelvärldens bredd.
*
* INDATA
*
* -
*
* UTDATA
*
* const int: Spelvärldens bredd.
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151214          Ursprungsversion
*
*/

const int World::getMapWidth() const
{
	return mapWidth_;
}

/*
* FUNKTION World::getMapHeight()
*
* BESKRIVNING
*
* Hämtar spelvärldens höjd.
*
* INDATA
*
* -
*
* UTDATA
*
* const int: Spelvärldens höjd.
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151214          Ursprungsversion
*
*/

const int World::getMapHeight() const
{
	return mapHeight_;
}

/*
* FUNKTION World::getTileVector()
*
* BESKRIVNING
*
* Hämtar listan över spelvärldens tiles.
*
* INDATA
*
* -
*
* UTDATA
*
* std::vector<int>: Lista över spelvärldens tiles.
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151214          Ursprungsversion
*
*/

const std::vector<int> World::getTileVector() const
{
	return tileVector_;
}

/*
* FUNKTION World::getNPCVector()
*
* BESKRIVNING
*
* Hämtar listan över spelvärldens alla NPC:er.
*
* INDATA
*
* -
*
* UTDATA
*
* std::map<int,NPC*>: Lista över spelvärldens alla NPC:er.
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151214          Ursprungsversion
*
*/

const std::map<int, NPC*> World::getNPCVector() const
{
	return NPCVector_;
}

/*
* FUNKTION World::getSensorVector()
*
* BESKRIVNING
*
* Hämtar listan över spelvärldens alla sensorer.
*
* INDATA
*
* -
*
* UTDATA
*
* std::map<int, Sensor*>: Lista över spelvärldens alla sensorer.
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151214          Ursprungsversion
*
*/

const std::map<int, Sensor*> World::getSensorVector() const
{
	return sensorVector_;
}

/*
* FUNKTION World::getEnemyVector()
*
* BESKRIVNING
*
* Hämtar listan över spelvärldens alla fiender.
*
* INDATA
*
* -
*
* UTDATA
*
* std::map<int, Enemy*>: Lista över spelvärldens alla fiender.
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151214          Ursprungsversion
*
*/

const std::map<int, Enemy*> World::getEnemyVector() const
{
	return enemyVector_;
}

/*
* FUNKTION World::getIntFromColor(sf::Color color)
*
* BESKRIVNING
*
* Översätter färger till heltal.
*
* INDATA
*
* color: Färgen som skall översättas.
*
* UTDATA
*
* int: Färgens motsvarande heltal.
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151214          Ursprungsversion
*
*/

int World::getIntFromColor(sf::Color color)
{
	switch (color.toInteger())
	{
	case 0x00FF00FF: //Gräs
		return 0;
	case 0xFF0000FF: //Träd på gräs
		return 1;
	case 0x7F6A00FF: //Bro
		return 2;
	case 0xFF8800FF: //Hus00
		return 3;
	case 0xFF8801FF: //Hus01
		return 4;
	case 0xFF8802FF: //Hus02
		return 5;
	case 0xFF8803FF: //Hus03
		return 6;
	case 0xFF8810FF: //Hus10
		return 7;
	case 0xFF8811FF: //Hus11
		return 8;
	case 0xFF8812FF: //Hus12
		return 9;
	case 0xFF8813FF: //Hus13
		return 10;
	case 0xFF8820FF: //Hus20
		return 11;
	case 0xFF8821FF: //Hus21
		return 12;
	case 0xFF8822FF: //Hus22
		return 13;
	case 0xFF8823FF: //Hus23
		return 14;
	case 0xFF8830FF: //Hus30
		return 15;
	case 0xFF8831FF: //Hus31
		return 16;
	case 0xFF8832FF: //Hus32
		return 17;
	case 0xFF8833FF: //Hus33
		return 18;
	case 0x7F7F7FFF: //Berg på gräs
		return 19;
	case 0x0000FFFF: //Vatten
		return 20;
	case 0xFF7F00FF: //Stubbe på gräs
		return 21;
	case 0x00FFFFFF: //Snö
		return 22;
	case 0xFFFF00FF: //Träd på gräs
		return 23;
	case 0xFF006EFF: //Kaktus
		return 24;
	case 0xFF6A00FF: //Sand
		return 25;
	case 0x404040FF: //Palm
		return 26;
	case 0xFF0022FF: //Lava
		return 100;
	case 0x808080FF: //Lavasten
		return 101;
	case 0x7F3300FF: //Nedbrunnet träd
		return 102;
	case 0x123456FF: //Fontän
		return 200;
	case 0xFF1000FF: //Sand (kan EJ gå på)
		return 201;
	case 0x7F1C00FF: //Nedbrunnet träd på gräs
		return 900;
	case 0x77617CFF: //Sten på gräs
		return 902;

	default:
		return -1;
	}
}

/*
* FUNKTION World::updateLists()
*
* BESKRIVNING
*
* Tar bort de fiender, NPC:er samt sensorer i spelvärlden som har blivit märkta med att de skall tas bort.
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
* 1                    151214          Ursprungsversion
*
*/

void World::updateLists()
{
	for (auto iter : removeEnemyVector_)
	{
		auto it = enemyVector_.find(iter);

		if (it != enemyVector_.end())
		{
			delete (it->second);
			enemyVector_.erase(it);
		}
	}
	removeEnemyVector_.clear();

	for (auto iter : removeNPCVector_)
	{
		auto it = NPCVector_.find(iter);

		if (it != NPCVector_.end())
		{
			delete (it->second);
			NPCVector_.erase(it);
		}
	}
	removeNPCVector_.clear();

	for (auto iter : removeSensorVector_)
	{
		auto it = sensorVector_.find(iter);

		if (it != sensorVector_.end())
		{
			delete (it->second);
			sensorVector_.erase(it);
		}
	}
	removeSensorVector_.clear();
}

/*
* SLUT PÅ FILEN World.cpp
*/