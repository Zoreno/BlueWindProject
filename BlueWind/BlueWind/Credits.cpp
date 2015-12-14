/*
* IDENTIFIERING
*
* Filnamn:    Credits.cpp
* Enhetsnamn: Credits
* Typ:        Definitioner hörande till klassen Help
* Revision:   1
* Skriven av: Simon Arkholt, Fredrik Gustafsson
*
*
* BESKRIVNING
*
* Denna implementeringsfil definierar medlemsfunktioner för klassen Help.
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

#include "Credits.h"
#include "Application.h"

using namespace std;

/*
* CALLBACK-FUNKTIONER (DEKLARATIONER)
*/

void creditsMenuCallback(Application*);		// Funktionen som körs då man klickar på knappen "Menu"

/*
* KONSTRUKTOR Credtis::Credits(Application* appPtr)
*
* BESKRIVNING
*
* Denna konstruktor skapar ett Credits-objekt.
*
* INDATA
*
* appPtr: Pekare till applikationen som Credits-objektet är en del av.
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

Credits::Credits(Application* appPtr)
	: Frame{ appPtr }
{
	addButton(sf::Vector2f(25, 600 - 65), sf::Vector2f(130, 50), "res/textures/menuButtonSmall.png", "res/textures/menuButtonSmallHover.png", creditsMenuCallback);
}

/*
* FUNKTION Credits::handleKeyEvent(sf::Event event)
*
* BESKRIVNING
*
* Hanterar ett tangenttryck genom att inte göra något med det.
*
* INDATA
*
* event: Ett tangenttryck
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

void Credits::handleKeyEvent(sf::Event event) {}

/*
* FUNKTION Credits::handleMouseEvent(sf::Event event)
*
* BESKRIVNING
*
* Hanterar musklick (vänster) på undermenyns knappar.
*
* INDATA
*
* event: Ett musklick
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

void Credits::handleMouseEvent(sf::Event event)
{
	switch (event.mouseButton.button)
	{
	case sf::Mouse::Left:
	{
		sf::Vector2i mousePosition{ appPointer_->getGameWindow().mapPixelToCoords(sf::Mouse::getPosition(appPointer_->getGameWindow())) };

		for (auto it : buttons_)
		{
			if (it->mouseOnButton(mousePosition))
			{
				it->clicked();
				break;
			}
		}
	}
	default:
		break;
	}
}

/*
* FUNKTION Credits::update()
*
* BESKRIVNING
*
* Uppdaterar undermenyns knappar.
*
* INDATA
*
* -
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

void Credits::update()
{
	for (auto it : buttons_)
	{
		it->update();
	}
}

/*
* FUNKTION Credits::render(GameWindow& window)
*
* BESKRIVNING
*
* Ritar upp undermenyn.
*
* INDATA
*
* window: Fönster som undermenyn ska ritas upp i.
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

void Credits::render(GameWindow& window)
{
	sf::Texture bTexture;
	if (!bTexture.loadFromFile("res/textures/credits.png"))
		throw FrameException("Kunde inte läsa in bild för Credits: res/textures/credits.png");

	background_.setTexture(bTexture);
	window.draw(background_);

	for (auto it : buttons_)
	{
		it->render(window);
	}
}

/*
* FUNKTION creditsMenuCallback(Application* ptr)
*
* BESKRIVNING
*
* Funktionen som körs då man klickar på knappen "Menu". Går ur undermenyn och öppnar startmenyn.
*
* INDATA
*
* ptr: Pekare till applikationen som undermenyn är en del av.
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

void creditsMenuCallback(Application* ptr)
{
	ptr->setNextFrame(new Menu(ptr));
}

/*
* SLUT PÅ FILEN Help.cpp
*/