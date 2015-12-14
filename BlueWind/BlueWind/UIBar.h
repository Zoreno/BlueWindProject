/*
* IDENTIFIERING
*
* Filnamn:    UIBar.h
* Enhetsnamn: UIBar
* Typ:        Moduldeklaration
* Revision:   1
* Skriven av: Joakim Bertils, Johannes Grundell
*
*
* BESKRIVNING
*
* Denna modul representerar en mätare på användargränssnittet.
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

#include <SFML\Graphics.hpp>
#include "GameWindow.h"
#include "UserInterface.h"

/*
* KLASS UIBar
*
* BASKLASSER
*
* -
*
* BESKRIVNING
*
* Klassen representerar en mätare på användargränssnittet.
*
* TILLSTÅND
*
* -
*
* KONSTRUKTORER
*
* UIBar(sf::Vector2f position, sf::Vector2f size, sf::Color color, std::string postfix, UserInterface* uiPtr)
*
* OPERATIONER
*
* -
*
* DATAMEDLEMMAR
*
* fillLevel_:	Anger hur stor del av mätaren som ska vara ifylld.
* size_:		Storlek på mätaren.
* position_:	Plats på skärmen som mätaren kommer att ritas.
* color_:		Färg på mätaren.
* postfix_:		Sträng som ska skrivas ut sist på mätaren.
* text_:		Sträng som ska skrivas ut på mätaren.
* ui_:			Pekare till användargränssnittet som mätaren är en del av.
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151120  Ursprungsversion
* 
*/

class UIBar
{
public:
	UIBar(sf::Vector2f, sf::Vector2f, sf::Color, std::string, UserInterface*);
	UIBar() = delete;
	UIBar(UIBar&) = delete;
	UIBar& operator=(const UIBar&) = delete;

	void update(int, int);
	void render(GameWindow&);

private:
	float fillLevel_;
	sf::Vector2f size_;
	sf::Vector2f position_;
	sf::Color color_;
	std::string postfix_;
	std::string text_;

	UserInterface* ui_;
}; //class UIBar

/*
* SLUT PÅ FILEN UIBar.h
*/