/*
* IDENTIFIERING
*
* Filnamn:    GameWindow.cpp
* Enhetsnamn: GameWindow
* Typ:        Definitioner hörande till klassen GameWindow
* Revision:   1
* Skriven av: Joakim Bertils, Johannes Grundell
*
*
* BESKRIVNING
*
* Denna implementeringsfil definierar medlemsfunktioner för klassen GameWindow.
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

#include "GameWindow.h"

/*
* KONSTRUKTOR GameWindow::GameWindow(sf::VideoMode videoMode, std::string title)
*
* BESKRIVNING
*
* Denna konstruktor skapar ett spelfönster.
*
* INDATA
*
* videoMode: Spelfönstrets storlek. 
* title: Spelfönstrets namn.
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

GameWindow::GameWindow(sf::VideoMode videoMode, std::string title)
	: sf::RenderWindow(videoMode, title)
{
}

/*
* SLUT PÅ FILEN GameWindow.cpp
*/