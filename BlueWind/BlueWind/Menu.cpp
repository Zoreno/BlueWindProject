/*
* IDENTIFIERING
*
* Filnamn:    Menu.cpp
* Enhetsnamn: Menu
* Typ:        Definitioner hörande till klassen Menu
* Revision:   1
* Skriven av: Simon Arkholt, Fredrik Gustafsson
*
*
* BESKRIVNING
*
* Denna implementeringsfil definierar medlemsfunktioner för klassen Menu.
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

#include "Menu.h"
#include "Application.h"
#include "GameOver.h"
#include "Help.h"
#include "Credits.h"

using namespace std;

/*
* CALLBACK-FUNKTIONER (DEKLARATIONER)
*/

void newGameCallback(Application*);		// Funktionen som körs då man klickar på knappen "New Game"
void loadGameCallback(Application*);	// Funktionen som körs då man klickar på knappen "Load Game"
void quitCallback(Application*);		// Funktionen som körs då man klickar på knappen "Quit"
void helpCallback(Application*);		// Funktionen som körs då man klickar på knappen "Help"
void creditsCallback(Application*);		// Funktionen som körs då man klickar på knappen "Credits"

/*
* KONSTRUKTOR Menu::Menu(Application* appPtr)
*
* BESKRIVNING
*
* Denna konstruktor konstruerar en startmeny.
*
* INDATA
*
* appPtr: Pekare till applikationen som startmenyn är en del av.
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

Menu::Menu(Application* appPtr)
	: Frame{ appPtr }
{
	addButton(sf::Vector2f(400 - 175, 150), sf::Vector2f(350, 100), "res/textures/newgameButton.png", "res/textures/newgameButtonHover.png", newGameCallback);
	addButton(sf::Vector2f(400 - 175, 275), sf::Vector2f(350, 100), "res/textures/loadgameButton.png", "res/textures/loadgameButtonHover.png", loadGameCallback);
	addButton(sf::Vector2f(400 - 175, 400), sf::Vector2f(350, 100), "res/textures/quitButton.png", "res/textures/quitButtonHover.png", quitCallback);
	addButton(sf::Vector2f(800 - 155, 600 - 65), sf::Vector2f(130, 50), "res/textures/helpButton.png", "res/textures/helpButtonHover.png", helpCallback);
	addButton(sf::Vector2f(25, 600 - 65), sf::Vector2f(130, 50), "res/textures/creditsButton.png", "res/textures/creditsButtonHover.png", creditsCallback);
	appPtr->getSoundHandler().playMusic("menuMusic");
}

/*
* FUNKTION Menu::handleKeyEvent(sf::Event event)
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

void Menu::handleKeyEvent(sf::Event event) {}

/*
* FUNKTION Menu::handleMouseEvent(sf::Event event)
*
* BESKRIVNING
*
* Hanterar musklick (vänster) på startmenyns knappar.
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

void Menu::handleMouseEvent(sf::Event event)
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
* FUNKTION Menu::update()
*
* BESKRIVNING
*
* Uppdaterar startmenyns knappar.
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

void Menu::update()
{
	for (auto it : buttons_)
	{
		it->update();
	}
}

/*
* FUNKTION Menu::render(GameWindow & window)
*
* BESKRIVNING
*
* Ritar upp startmenyn.
*
* INDATA
*
* window: Fönster som startmenyn ska ritas upp i.
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

void Menu::render(GameWindow& window)
{
	sf::Texture bTexture;
	if (!bTexture.loadFromFile("res/textures/Menu.png"))
		throw FrameException("Kunde inte läsa in bild för Menu: res/textures/Menu.png");

	background_.setTexture(bTexture);
	window.draw(background_);

	for (auto it : buttons_)
	{
		it->render(window);
	}
}

/*
* FUNKTION newGameCallback(Application* ptr)
*
* BESKRIVNING
*
* Funktionen som körs då man klickar på knappen "New Game". Går ur startmenyn och startar ett nytt spel.
*
* INDATA
*
* ptr: Pekare till applikationen som startmenyn är en del av.
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

void newGameCallback(Application* ptr)
{
	ptr->setNextFrame(new Game(ptr));
}

/*
* FUNKTION loadGameCallback(Application* ptr)
*
* BESKRIVNING
*
* Funktionen som körs då man klickar på knappen "Load Game". Går ur startmenyn och laddar det sparade spelet.
*
* INDATA
*
* ptr: Pekare till applikationen som startmenyn är en del av.
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

void loadGameCallback(Application* ptr)
{
	ptr->setNextFrame(new Game(ptr, true));
}

/*
* FUNKTION quitCallback(Application* ptr)
*
* BESKRIVNING
*
* Funktionen som körs då man klickar på knappen "Quit". Går ur startmenyn och stänger ner programmet.
*
* INDATA
*
* ptr: Pekare till applikationen som startmenyn är en del av.
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

void quitCallback(Application* ptr)
{
	ptr->getGameWindow().close();
}

/*
* FUNKTION helpCallback(Application* ptr)
*
* BESKRIVNING
*
* Funktionen som körs då man klickar på knappen "Help". Går ur startmenyn och öppnar en frame med info om spelets kontroller.
*
* INDATA
*
* ptr: Pekare till applikationen som startmenyn är en del av.
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

void helpCallback(Application* ptr)
{
	ptr->setNextFrame(new Help(ptr));
}

/*
* FUNKTION creditsCallback(Application* ptr)
*
* BESKRIVNING
*
* Funktionen som körs då man klickar på knappen "Credtis". Går ur startmenyn och öppnar en undermeny med en lista över i spelet använt material.
*
* INDATA
*
* ptr: Pekare till applikationen som startmenyn är en del av.
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

void creditsCallback(Application* ptr)
{
	ptr->setNextFrame(new Credits(ptr));
}

/*
* SLUT PÅ FILEN Menu.cpp
*/