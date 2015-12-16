/*
* IDENTIFIERING
*
* Filnamn:    FrameButton.h
* Enhetsnamn: FrameButton
* Typ:        Moduldeklaration
* Revision:   1
* Skriven av: Simon Arkeholt, Fredrik Gustafsson
*
*
* BESKRIVNING
*
* Denna modul representerar en knapp i spelet.
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
#include <functional>
#include <stdexcept>
#include "GameWindow.h"

/*
* Framåtdeklarationer
*/

class Application;

/*
* KLASS FrameButtonException
*
* BASKLASSER
*
* std::logic_error
*
* BESKRIVNING
*
* Klassen kastar undantag för FrameButton.
*
* KONSTRUKTORER
*
* Ärver från std::logic_error.
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

class FrameButtonException : public std::logic_error
{
public:
	using std::logic_error::logic_error;
};

/*
* KLASS FrameButton
*
* BASKLASSER
*
* -
*
* BESKRIVNING
*
* Klassen representerar en knapp i spelet.
*
* KONSTRUKTORER
*
* FrameButton(Application*,sf::Vector2f, sf::Vector2f, std::string, std::string, std::function<void (Application*)>)
*
* DATAMEDLEMMAR
*
* appPointer_:		Pekare till den applikation knappen är en del av.
* position_:		Knappens position.
* size_:			Knappens storlek.
* normalTexture_:	Den textur som ska ritas upp på knappen då man EJ håller musen över den.
* hoverTexture_:	Den textur som ska ritas upp på knappen då man håller musen över den.
* sprite_:			Den bild som ritas upp på knappen.
* callback_:		Den funktion som anropas då knappen klickas på.
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151214  Ursprungsversion
*
*/

class FrameButton
{
public:
	FrameButton(Application*, sf::Vector2f, sf::Vector2f, std::string, std::string, std::function<void(Application*)>);
	FrameButton(const FrameButton&) = delete;
	FrameButton& operator=(const FrameButton&) = delete;

	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;

	void update();
	void render(GameWindow&);
	void clicked();
	bool mouseOnButton(sf::Vector2i);

private:
	Application* appPointer_;
	sf::Vector2f position_;
	sf::Vector2f size_;
	sf::Texture normalTexture_;
	sf::Texture hoverTexture_;
	sf::Sprite sprite_;
	std::function<void(Application*)> callback_;
}; // class FrameButton

/*
* SLUT PÅ FILEN FrameButton.h
*/