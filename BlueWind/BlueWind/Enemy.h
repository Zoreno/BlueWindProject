/*
* IDENTIFIERING
*
* Filnamn:    Enemy.h
* Enhetsnamn: Enemy
* Typ:        Moduldeklaration
* Revision:   1
* Skriven av: Jonas Ehn, Olle Andersson
*
*
* BESKRIVNING
*
* Denna modul representerar entities av fiendetyp
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

#include "Entity.h"
#include "GameWindow.h"
#include <functional>

/*
* LOKALA FUNKTIONER (DEKLARATIONER)
*/

float getDistance(sf::Vector2f, sf::Vector2f);
sf::Vector2f normalize(sf::Vector2f);

/*
* KLASS Enemy
*
* BASKLASSER
*
* Entity
*
* BESKRIVNING
*
* Klassen representerar entity-objekt av fiendekaraktär
*
* TILLSTÅND
*
* -
*
* KONSTRUKTORER
*
* Enemy(int level, int health, int damage, int ID, std::string name, sf::Vector2f position, World * worldPtr,
		sf::Texture& texture, std::function<void(Enemy*)> callbackFunc)
*
* OPERATIONER
*
* -
*
* DATAMEDLEMMAR
*
* startPosition_ :	Den position som fienden utgår ifrån
* state_ :			Fiendens tillstånd
* attackCooldown_ :	En timer som förhindrar att fienderna skadar spelaren för ofta
* resetTimer_ :		En timer som uppmärksammar om fienden fastnat vid något hinder
* deathFkn_ :		En funktion som körs när fienden dör	
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151120  Ursprungsversion
*
*/

class Enemy : public Entity
{
public:
	enum STATES { ATTACK, MOVETOPLAYER, IDLE, RESET };

	Enemy(int, int, int, int, std::string, sf::Vector2f, World*, sf::Texture&, std::function<void(Enemy*)>);
	Enemy() = delete;
	Enemy(const Enemy&) = delete;
	Enemy& operator=(const Enemy&) = delete;

	void update() override;
	void render(GameWindow&) override;

	void die() override;

private:
	const sf::Vector2f startPosition_;
	STATES state_{ IDLE };

	int attackCooldown_{ 0 };
	int resetTimer_{ 0 };

	void updateState();
	void executeState();
	std::function<void(Enemy*)> deathFkn_;
	void attackPlayer();
};// class Enemy

  /*
  * SLUT PÅ FILEN Enemy.h
  */