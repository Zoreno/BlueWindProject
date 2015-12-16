/*
* IDENTIFIERING
*
* Filnamn:    GameWon.h
* Enhetsnamn: GameWon
* Typ:        Moduldeklaration
* Revision:   1
* Skriven av: Simon Arkeholt, Fredrik Gustafsson
*
*
* BESKRIVNING
*
* Denna modul representerar en meny som visas då spelaren vinner spelet.
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

#include "Frame.h"
#include "GameWindow.h"

/*
* Framåtdeklarationer
*/

class Application;

/*
* KLASS GameWon
*
* BASKLASSER
*
* Frame
*
* BESKRIVNING
*
* Klassen representerar en meny som visas då spelaren vinner spelet.
*
* KONSTRUKTORER
*
* GameWon(Application*)
*
* DATAMEDLEMMAR
*
* background_: Menyns bakgrundsbild.
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151214  Ursprungsversion
*
*/

class GameWon : public Frame
{
public:
	GameWon(Application*);
	GameWon(const GameWon&) = delete;
	GameWon& operator=(const GameWon&) = delete;

	void handleKeyEvent(sf::Event) override;
	void handleMouseEvent(sf::Event) override;

	void update() override;
	void render(GameWindow&) override;
private:
	sf::Sprite background_;
}; // class GameWon

/*
* SLUT PÅ FILEN GameWon.h
*/