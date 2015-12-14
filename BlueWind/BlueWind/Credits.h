/*
* IDENTIFIERING
*
* Filnamn:    Credits.h
* Enhetsnamn: Credits
* Typ:        Moduldeklaration
* Revision:   1
* Skriven av: Simon Arkeholt, Fredrik Gustafsson
*
*
* BESKRIVNING
*
* Denna modul representerar en undermeny till spelets startmeny där en lista över det material som använts i spelet visas.
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
* KLASS Credits
*
* BASKLASSER
*
* Frame
*
* BESKRIVNING
*
* Klassen representerar en undermeny till spelets startmeny där en lista över det material som använts i spelet visas.
*
* TILLSTÅND
*
* -
*
* KONSTRUKTORER
*
* Credits(Application*)
*
* OPERATIONER
*
* -
*
* DATAMEDLEMMAR
*
* background_: Undermenyns bakgrundsbild.
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151214  Ursprungsversion
*
*/

class Credits : public Frame
{
public:
	Credits(Application*);
	Credits(const Credits&) = delete;
	Credits& operator=(const Credits&) = delete;

	void handleKeyEvent(sf::Event) override;
	void handleMouseEvent(sf::Event) override;

	void update() override;
	void render(GameWindow&) override;

private:
	sf::Sprite background_;
}; // class Credits

/*
* SLUT PÅ FILEN Credits.h
*/