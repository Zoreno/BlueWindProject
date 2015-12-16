/*
* IDENTIFIERING
*
* Filnamn:    UIBar.h
* Enhetsnamn: UIBar
* Typ:        Moduldeklaration
* Revision:   1
* Skriven av: Joakim Bertils, Johannes Grundell
*
*
* BESKRIVNING
*
* Denna modul representerar en mätare på användargränssnittet.
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

#include <map>
#include "Entity.h"
#include "Inventory.h"

/*
* FRAMÅTDEKLARATIONER
*/

class World;
class Game;
class Enemy;
class NPC;

/*
* KLASS Player
*
* BASKLASSER
*
* Entity
*
* BESKRIVNING
*
* Klassen representerar spelaren
*
* KONSTRUKTORER
*
* Player(World*, sf::Texture&, Game*);
*
*
* DATAMEDLEMMAR
*
* experience_:		Erfarenhetspoäng till spelaren
* mana_:			Magipoäng till spelaren
* maxMana_:			Maximala antalet magipoäng till spelaren
* gamePointer_:		En pekare till spelet
* inventory_:		Spelarens väska
* healthCounter_:	Ett helttalsvärde med spelarens hälsopoäng
* manaCounter_:		Ett helttalsvärde med spelarens magipoäng
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151120  Ursprungsversion
*
*/
class Player : public Entity
{
public:
	Player(World*, sf::Texture&, Game*);
	Player(const Player&) = delete;
	Player() = delete;
	Player& operator=(const Player&) = delete;

	int getExperience() const;
	void addExperience(int);
	int getMana() const;
	void setMana(int);
	void addMana(int);
	int getMaxMana() const;
	void setMaxMana(int);
	int getMaxExperience();

	void setName(std::string);
	void setMaxHealth(int);
	void setDamage(int);
	void setLevel(int);
	void setExperience(int);

	Inventory* getInventory();

	void swordAttack(const std::map<int, Enemy*>&);
	void fireballAttack(const std::map<int, Enemy*>&);
	void interact(const std::map<int, NPC*>&);

	int getXpToLevel();
	bool checkForLevelup();

	void update() override;
	void render(GameWindow&) override;

	void die() override;

private:
	void checkSensors();

	int experience_{ 0 };
	int mana_;
	int maxMana_;
	Game* gamePointer_;
	Inventory inventory_;
	int healthCounter_;
	int manaCounter_;
};