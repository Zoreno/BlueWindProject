/*
* IDENTIFIERING
*
* Filnamn:    GameOver.h
* Enhetsnamn: GameOver
* Typ:        Moduldeklaration
* Revision:   1
* Skriven av: Simon Arkeholt, Fredrik Gustafsson
*
*
* BESKRIVNING
*
* Denna modul representerar en meny som visas då spelaren förlorar spelet.
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
* KLASS GameOver
*
* BASKLASSER
*
* Frame
*
* BESKRIVNING
*
* Klassen representerar en meny som visas då spelaren förlorar spelet.
*
* TILLSTÅND
*
* -
*
* KONSTRUKTORER
*
* GameOver(Application*)
*
* OPERATIONER
*
* -
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

class GameOver : public Frame
{
public:
	GameOver(Application*);
	GameOver(const GameOver&) = delete;
	GameOver& operator=(const GameOver&) = delete;

	void handleKeyEvent(sf::Event) override;
	void handleMouseEvent(sf::Event) override;

	void update() override;
	void render(GameWindow&) override;

private:
	sf::Sprite background_;
}; // class GameOver

/*
* SLUT PÅ FILEN GameOver.h
*/