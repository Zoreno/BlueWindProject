/*
* IDENTIFIERING
*
* Filnamn:    Menu.h
* Enhetsnamn: Menu
* Typ:        Moduldeklaration
* Revision:   1
* Skriven av: Simon Arkeholt, Fredrik Gustafsson
*
*
* BESKRIVNING
*
* Denna modul representerar spelets startmeny.
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
* KLASS Menu
*
* BASKLASSER
*
* Frame
*
* BESKRIVNING
*
* Klassen representerar spelets startmeny.
*
* KONSTRUKTORER
*
* Menu(Application*)
*
* DATAMEDLEMMAR
*
* background_: Startmenyns bakgrundsbild.
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151214  Ursprungsversion
*
*/

class Menu : public Frame
{
public:
	Menu(Application*);
	Menu(const Menu&) = delete;
	Menu& operator=(const Menu&) = delete;

	void handleKeyEvent(sf::Event) override;
	void handleMouseEvent(sf::Event) override;

	void update() override;
	void render(GameWindow&) override;
private:
	sf::Sprite background_;
}; // class Menu

/*
* SLUT PÅ FILEN Menu.h
*/