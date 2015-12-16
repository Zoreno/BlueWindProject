/*
* IDENTIFIERING
*
* Filnamn:    Input.h
* Enhetsnamn: Input
* Typ:        Definitioner hörande till klass Input
* Revision:   1
* Skriven av: Olle Andersson, Jonas Ehn
*
*
* BESKRIVNING
*
* Denna implementeringsfil definierar medlemsfunktioner för klassen Input.
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

#include <map>
#include "GameWindow.h"
#include "FrameButton.h"

/*
* KLASS Input
*
* BASKLASSER
*
* -
*
* BESKRIVNING
*
* Klassen hanterar input från användaren
*
* KONSTRUKTORER
*
* Input(Application * appPtr)
* appPtr :				En pekare till applikationen
*
* DATAMEDLEMMAR
*
* appPointer_ :			En pekare till applikationen
* pressedButtons_ :		En map som innehåller de knappar som trycks ner
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151120  Ursprungsversion
*
*/

class Input
{
public:
	Input(Application*);
	Input(const Input&) = delete;
	Input() = delete;
	Input& operator=(const Input&) = delete;

	bool isPressed(char) const;

	void update();

	void keyPressed(sf::Event);
	void mousePressed(sf::Event);

private:
	Application* appPointer_;
	std::map<char, bool> pressedButtons_;
};//Class Input

/*
* Slut på filen Input.h
*/