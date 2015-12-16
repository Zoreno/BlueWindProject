/*
* IDENTIFIERING
*
* Filnamn:    GameWindow.h
* Enhetsnamn: GameWindow
* Typ:        Moduldeklaration
* Revision:   1
* Skriven av: Joakim Bertils, Johannes Grundell
*
*
* BESKRIVNING
*
* Denna modul representerar ett spelfönster.
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

#include <SFML\Graphics.hpp>
#include <string>

/*
* KLASS GameWindow
*
* BASKLASSER
*
* sf::RenderWindow
*
* BESKRIVNING
*
* Klassen representerar ett spelfönster.
*
* KONSTRUKTORER
*
* GameWindow(sf::VideoMode, std::string)
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

class GameWindow : public sf::RenderWindow
{
public:
	GameWindow(sf::VideoMode, std::string);
	GameWindow(const GameWindow&) = delete;
	GameWindow& operator=(const GameWindow&) = delete;
};

/*
* SLUT PÅ FILEN GameWindow.h
*/