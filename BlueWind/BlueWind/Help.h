/*
* IDENTIFIERING
*
* Filnamn:    Help.h
* Enhetsnamn: Help
* Typ:        Moduldeklaration
* Revision:   1
* Skriven av: Simon Arkeholt, Fredrik Gustafsson
*
*
* BESKRIVNING
*
* Denna modul representerar en undermeny till spelets startmeny där spelets kontroller visas.
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
* KLASS Help
*
* BASKLASSER
*
* Frame
*
* BESKRIVNING
*
* Klassen representerar en undermeny till spelets startmeny där spelets kontroller visas.
*
* TILLSTÅND
*
* -
*
* KONSTRUKTORER
*
* Help(Application*)
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

class Help : public Frame
{
public:
	Help(Application*);
	Help(const Help&) = delete;
	Help& operator=(const Help&) = delete;

	void handleKeyEvent(sf::Event) override;
	void handleMouseEvent(sf::Event) override;

	void update() override;
	void render(GameWindow&) override;

private:
	sf::Sprite background_;
}; // class Help

   /*
   * SLUT PÅ FILEN Menu.h
   */