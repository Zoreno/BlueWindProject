/*
* IDENTIFIERING
*
* Filnamn:    Frame.h
* Enhetsnamn: Frame
* Typ:        Moduldeklaration
* Revision:   1
* Skriven av: Joakim Bertils, Johannes Grundell
*
*
* BESKRIVNING
*
* Denna modul representerar saker som kan placeras i spelfönstret. TODO Bättre beskrivning?!
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

#include "GameWindow.h"
#include "FrameButton.h"
#include <stdexcept>

/*
* Framåtdeklarationer
*/

class Application;

/*
* KLASS FrameException
*
* BASKLASSER
*
* std::logic_error
*
* BESKRIVNING
*
* Klassen kastar undantag i Frame.
*
* TILLSTÅND
*
* -
*
* KONSTRUKTORER
*
* default-konstruktor. TODO Hur??
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

class FrameException : public std::logic_error
{
public:
	using std::logic_error::logic_error;
};

/*
* KLASS Frame
*
* BASKLASSER
*
* -
*
* BESKRIVNING
*
* Klassen representerar saker som kan placeras i spelfönstret. Basklass till "Game" samt alla menyer.
*
* TILLSTÅND
*
* -
*
* KONSTRUKTORER
*
* Frame(Application*)
*
* OPERATIONER
*
* -
*
* DATAMEDLEMMAR
*
* buttons_: Frame-objektets alla knappar.
* appPointer_: Pekare till applikationen.
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151214  Ursprungsversion
*
*/

class Frame
{
public:
	Frame(Application*);
	Frame(const Frame&) = delete;
	Frame& operator=(const Frame&) = delete;

	virtual void update() = 0;
	virtual void render(GameWindow&) = 0;

	virtual void handleKeyEvent(sf::Event) = 0;
	virtual void handleMouseEvent(sf::Event) = 0;

	virtual ~Frame();

	void addButton(sf::Vector2f, sf::Vector2f, std::string, std::string, std::function<void(Application*)>);

protected:
	std::vector<FrameButton*> buttons_;
	Application* appPointer_;
}; // class Frame

/*
* SLUT PÅ FILEN Frame.h
*/