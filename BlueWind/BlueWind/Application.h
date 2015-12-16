/*
* IDENTIFIERING
*
* Filnamn:    Application.h
* Enhetsnamn: Application
* Typ:        Moduldeklaration
* Revision:   1
* Skriven av: Joakim Bertils
*
*
* BESKRIVNING
*
* Denna modul representerar hela applikationen
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
#include "Menu.h"
#include "Game.h"
#include "Input.h"
#include "SoundHandler.h"

/*
* KLASS Application
*
* BASKLASSER
*
* -
*
* BESKRIVNING
*
* Klassen representerar spelapplikationen
*
* TILLSTÅND
*
* -
*
* KONSTRUKTORER
*
* Application()
*
* OPERATIONER
*
* -
*
* DATAMEDLEMMAR
*
* window_ :			Ett fönster
* currentFrame_ :	Den nuvarande framen
* nextFrame_ :		Nästa frame
* input_ :			Ett input-objekt som hanterar input
* soundHandler_ :	Ett ljudhanteringsobjekt
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151120  Ursprungsversion
*
*/

class Application
{
public:
	Application();
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
	~Application();

	void run();

	void render(GameWindow& window);
	void update();
	Frame* getCurrentFrame();
	void changeCurrentFrame();
	void setNextFrame(Frame*);

	const Input& getInput();

	GameWindow& getGameWindow();
	SoundHandler& getSoundHandler();

private:
	GameWindow window_{ sf::VideoMode(800, 600), "Bluewind" };
	Frame* currentFrame_;
	Frame* nextFrame_; 
	Input input_;
	SoundHandler soundHandler_;
}; //class Application

   /*
   * SLUT PÅ FILEN Application.h
   */