/*
* IDENTIFIERING
*
* Filnamn:    GameOver.cpp
* Enhetsnamn: GameOver
* Typ:        Definitioner hörande till klassen GameOver
* Revision:   1
* Skriven av: Simon Arkholt, Fredrik Gustafsson
*
*
* BESKRIVNING
*
* Denna implementeringsfil definierar medlemsfunktioner för klassen GameOver.
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

#include "GameOver.h"
#include "Application.h"

using namespace std;

/*
* CALLBACK-FUNKTIONER (DEKLARATIONER)
*/

void menuCallback(Application*);	// Funktionen som körs då man klickar på knappen "Main Menu"

/*
* KONSTRUKTOR GameOver::GameOver(Application* appPtr)
*
* BESKRIVNING
*
* Denna konstruktor skapar ett GameOver-objekt.
*
* INDATA
*
* appPtr: Pekare till applikationen som GameOver-objektet är en del av.
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

GameOver::GameOver(Application* appPtr)
	: Frame{ appPtr }
{
	addButton(sf::Vector2f(400 - 175, 365), sf::Vector2f(350, 100), "res/textures/menuButton.png", "res/textures/menuButtonHover.png", menuCallback);
	appPtr->getSoundHandler().playMusic("gameOverMusic");
}

/*
* FUNKTION GameOver::handleKeyEvent(sf::Event event)
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
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151214          Ursprungsversion
*
*/

void GameOver::handleKeyEvent(sf::Event event) {}

/*
* FUNKTION GameOver::handleMouseEvent(sf::Event event)
*
* BESKRIVNING
*
* Hanterar musklick (vänster) på menyns knappar.
*
* INDATA
*
* event: Ett musklick
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

void GameOver::handleMouseEvent(sf::Event event)
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
* FUNKTION GameOver::update()
*
* BESKRIVNING
*
* Uppdaterar menyns knappar.
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

void GameOver::update()
{
	for (auto it : buttons_)
	{
		it->update();
	}
}

/*
* FUNKTION GameOver::render(GameWindow& window)
*
* BESKRIVNING
*
* Ritar upp menyn.
*
* INDATA
*
* window: Fönster som menyn ska ritas upp i.
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

void GameOver::render(GameWindow& window)
{
	sf::Texture bTexture;
	if (!bTexture.loadFromFile("res/textures/GameOver.png"))
		throw FrameException("Kunde inte läsa in bild för GameOver: res/textures/GameOver.png");

	background_.setTexture(bTexture);
	window.draw(background_);

	for (auto it : buttons_)
	{
		it->render(window);
	}
}

/*
* FUNKTION menuCallback(Application* ptr)
*
* BESKRIVNING
*
* Funktionen som körs då man klickar på knappen "Main Menu". Går ur menyn och öppnar startmenyn.
*
* INDATA
*
* ptr: Pekare till applikationen som menyn är en del av.
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

void menuCallback(Application* ptr)
{
	ptr->setNextFrame(new Menu(ptr));
}

/*
* SLUT PÅ FILEN GameOver.cpp
*/