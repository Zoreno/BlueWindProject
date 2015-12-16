/*
* IDENTIFIERING
*
* Filnamn:    FrameButton.cpp
* Enhetsnamn: FrameButton
* Typ:        Definitioner hörande till klassen FrameButton
* Revision:   1
* Skriven av: Simon Arkholt, Fredrik Gustafsson
*
*
* BESKRIVNING
*
* Denna implementeringsfil definierar medlemsfunktioner för klassen FrameButton.
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

#include "FrameButton.h"
#include "Application.h"

using namespace std;

/*
* KONSTRUKTOR FrameButton::FrameButton(Application* appPtr, sf::Vector2f pos, sf::Vector2f size, std::string normalFile, std::string hoverFile, std::function<void(Application*)> callbackFunc)
*
* BESKRIVNING
*
* Denna konstruktor skapar en knapp.
*
* INDATA
*
* appPtr:		Pekare till applikationen som knappen ska vara en del av.
* pos:			Knappens position.
* size:			Knappens storlek.
* normalFile:	Fil som innehåller knappens "normalTexture_".
* hoverFile:	Fil som innehåller knappens "hoverTexture_".
* callbackFunc	Funktionen som anropas då knappen klickas på.
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

FrameButton::FrameButton(Application* appPtr, sf::Vector2f pos, sf::Vector2f size, std::string normalFile, std::string hoverFile, std::function<void(Application*)> callbackFunc)
	: appPointer_{ appPtr },
	position_{ pos },
	size_{ size },
	callback_{ callbackFunc }
{
	if (!normalTexture_.loadFromFile(normalFile))
		throw FrameButtonException("Kunde inte läsa in textur för knapp från fil:" + normalFile);
	if (!hoverTexture_.loadFromFile(hoverFile))
		throw FrameButtonException("Kunde inte läsa in textur för knapp från fil:" + hoverFile);
}

/*
* FUNKTION FrameButton::getPosition()
*
* BESKRIVNING
*
* Hämtar knappens position.
*
* INDATA
*
* -
*
* UTDATA
*
* sf::Vector2f: Knappens position.
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151214          Ursprungsversion
*
*/

sf::Vector2f FrameButton::getPosition() const
{
	return position_;
}

/*
* FUNKTION FrameButton::getSize()
*
* BESKRIVNING
*
* Hämtar knappens storlek.
*
* INDATA
*
* -
*
* UTDATA
*
* sf::Vector2f: Knappens storlek.
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151214          Ursprungsversion
*
*/

sf::Vector2f FrameButton::getSize() const
{
	return size_;
}

/*
* FUNKTION FrameButton::update()
*
* BESKRIVNING
*
* Uppdaterar knappen.
*
* INDATA
*
* -
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

void FrameButton::update()
{
	sf::Vector2i mousePosition{ appPointer_->getGameWindow().mapPixelToCoords(sf::Mouse::getPosition(appPointer_->getGameWindow())) };

	if (mouseOnButton(mousePosition))
		sprite_.setTexture(hoverTexture_);
	else
		sprite_.setTexture(normalTexture_);
}

/*
* FUNKTION FrameButton::render(GameWindow& window)
*
* BESKRIVNING
*
* Ritar upp knappen.
*
* INDATA
*
* window: Fönster som knappen ska ritas upp i.
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

void FrameButton::render(GameWindow& window)
{
	sprite_.setPosition(position_);
	window.draw(sprite_);
}

/*
* FUNKTION FrameButton::clicked()
*
* BESKRIVNING
*
* Funktionen som anropas då knappen klickas på.
*
* INDATA
*
* -
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

void FrameButton::clicked()
{
	appPointer_->getSoundHandler().playSound("menuClick");
	callback_(appPointer_);
}

/*
* FUNKTION FrameButton::mouseOnButton(sf::Vector2i mousePosition)
*
* BESKRIVNING
*
* Kontrollerar om musen hålls över knappen.
*
* INDATA
*
* mousePosition: Musens position.
*
* UTDATA
*
* bool: Anger om musen hålls över knappen (true) eller ej.
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151214          Ursprungsversion
*
*/

bool FrameButton::mouseOnButton(sf::Vector2i mousePosition)
{
	return (mousePosition.x > position_.x && mousePosition.x < position_.x + size_.x &&
			mousePosition.y > position_.y && mousePosition.y < position_.y + size_.y);
}

/*
* SLUT PÅ FILEN FrameButton.cpp
*/