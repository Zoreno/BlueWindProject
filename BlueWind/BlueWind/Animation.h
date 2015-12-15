/*
* IDENTIFIERING
*
* Filnamn:    Animation.h
* Enhetsnamn: Animation
* Typ:        Definitioner hörande till klass Animation
* Revision:   1
* Skriven av: Joakim Bertils, Jonas Ehn
*
*
* BESKRIVNING
*
* Denna implementeringsfil definierar medlemsfunktioner för klassen Animation.
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151120  Ursprungsversion
*/

#pragma once

/*
* REFERERADE BIBLIOTEK OCH MODULER
*/

#include <vector>
#include <string>
#include <SFML\Graphics.hpp>
#include "GameWindow.h"

/*
* FRAMÅTDEKLARATIONER
*/

class Entity;

/*
* KLASS Animation
*
* BASKLASSER
*
* -
*
* BESKRIVNING
*
* Klassen representerar en animation för ett entity-objekt
*
* TILLSTÅND
*
* -
*
* KONSTRUKTORER
*
* Animation(Entity* entityPointer, sf::Texture& tex)
* entityPointer:		En pekare till det entity-objekt som animationen är		
*						kopplad till
* tex:					Det texturobjekt som ska flyttas in i spriten.
*
* OPERATIONER
*
* -
*
* DATAMEDLEMMAR
*
* currentSprite_ :		Den nuvarande spriten som ska ritas ut.
* texture_ :			Texturen som används i spriten.
* counter_ :			Räknare som styr uppdateringsfrekvensen.
* animState_ :			State som håller reda på vad vi ska plocka ur 
*						sprite-sheetet.
* attackCounter_ :		Räknare som håller kvar attack-spriten en 
*						liten extra stund.
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151120  Ursprungsversion
*
*/

class Animation
{
public:
	Animation(Entity*, sf::Texture&);
	Animation() = delete;
	Animation(const Animation&) = delete;
	Animation& operator=(const Animation&) = delete;

	void update(int,int, bool);
	void render(GameWindow&);

private:
	sf::Sprite currentSprite_;
	sf::Texture& texture_;

	int counter_;
	int animState_;
	int attackCounter_;

	Entity* entityPtr_;
}; //Class Animation

  /*
  * SLUT PÅ FILEN Animation.h
  */