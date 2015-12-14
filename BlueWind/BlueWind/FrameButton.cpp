/*
* IDENTIFIERING
*
* Filnamn:    FrameButton.cpp
* Enhetsnamn:
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

////////// FORTSÄTT HÄR FREDRIK!!

/*
* KONSTRUKTOR FrameButton(Application* appPtr, sf::Vector2f pos, sf::Vector2f size, std::string normalFile, std::string hoverFile, std::function<void(Application*)> callbackFunc)
*
* BESKRIVNING
*
* Denna konstruktor skapar ett GameWon-objekt.
*
* INDATA
*
* appPtr:		Pekare till applikationen som GameWon-objektet är en del av.
*
* UTDATA
*
* -
*
* SIDOEFFEKTER
*
* -
*
* UTNYTTJAR
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
	callback_{callbackFunc}
{
	if (!normalTexture_.loadFromFile(normalFile))
		throw FrameButtonException("Kunde inte läsa in textur för knapp från fil:" + normalFile);
	if (!hoverTexture_.loadFromFile(hoverFile))
		throw FrameButtonException("Kunde inte läsa in textur för knapp från fil:" + hoverFile);
}

sf::Vector2f FrameButton::getPosition() const
{
	return position_;
}

sf::Vector2f FrameButton::getSize() const
{
	return size_;
}

void FrameButton::update()
{
	sf::Vector2i mousePosition{ appPointer_->getGameWindow().mapPixelToCoords(sf::Mouse::getPosition(appPointer_->getGameWindow())) };
		
	if (mouseOnButton(mousePosition))
		sprite_.setTexture(hoverTexture_);
	else
		sprite_.setTexture(normalTexture_);	
}

void FrameButton::render(GameWindow & window)
{
	sprite_.setPosition(position_);
	window.draw(sprite_);
}

void FrameButton::clicked()
{
	appPointer_->getSoundHandler().playSound("menuClick");
	callback_(appPointer_);
}

bool FrameButton::mouseOnButton(sf::Vector2i mousePosition)
{
	return (mousePosition.x > position_.x && mousePosition.x < position_.x + size_.x &&
			mousePosition.y > position_.y && mousePosition.y < position_.y + size_.y);
}