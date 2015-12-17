/*
* IDENTIFIERING
*
* Filnamn:    UIInventoryFrame.cpp
* Enhetsnamn: UIInventoryFrame
* Typ:        Definitioner hörande till klass UIInventoryFrame
* Revision:   1
* Skriven av: Joakim Bertils, Johannes Grundell
*
*
* BESKRIVNING
*
* Denna implementeringsfil definierar medlemsfunktioner för klassen UIInventoryFrame.
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151120  Ursprungsversion
*/

/*
* REFERERADE BIBLIOTEK OCH MODULER
*/

#include <algorithm>
#include <string>
#include "UIInventoryFrame.h"

using namespace std;

/*
* KONSTRUKTOR UIInventoryFrame(UserInterface * uiPtr, Player * playerPtr)
*
* BESKRIVNING
*
* Denna konstruktor konstruerar ett fönster för spelarens föremål.
*
* INDATA
*
* uiPtr:		Pekare till användargränssnittet.
* playerPtr:	Pekare till spelaren.
*
* UTDATA
*
* -
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

UIInventoryFrame::UIInventoryFrame(UserInterface * uiPtr, Player * playerPtr)
	:UIComponent{ sf::Vector2f(480,50), sf::Vector2f(300,500), uiPtr, playerPtr , false}
{
	playerInventory_ = playerPtr->getInventory();
	inventorySize_ = playerInventory_->getMaxSize();
}

/*
* FUNKTION UIInventoryFrame::update()
*
* BESKRIVNING
*
* Uppdaterar föremålsfönstret.
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
* 1                    151120          Ursprungsversion
*
*/

void UIInventoryFrame::update() {}

/*
* FUNKTION UIInventoryFrame::render(GameWindow & window)
*
* BESKRIVNING
*
* Ritar föremålsfönstret på window.
*
* INDATA
*
* window:	Fönster som föremålsfönstret ska ritas på.
*
* UTDATA
*
* -
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

void UIInventoryFrame::render(GameWindow & window)
{
	sf::RectangleShape frame{ size_ };
	frame.setPosition(position_);
	frame.setFillColor(sf::Color{ 200,200,200,200 });
	frame.setOutlineColor(sf::Color{ 100,100,100,255 });
	frame.setOutlineThickness(4.0f);
	window.draw(frame);

	sf::Text conversationText{ "Inventory", ui_->getFont(), 40 };
	conversationText.setPosition(position_ + sf::Vector2f(10, 16 ));
	conversationText.setColor(sf::Color::Black);
	window.draw(conversationText);

	for (int i{ 0 }; i <  (min((int)inventorySize_, playerInventory_->getSize())); ++i)
	{
		Item* item = playerInventory_->at(i);
		item->render(window, position_ + sf::Vector2f(10.0f, 80.0f + 52.0f * i));

		sf::Text conversationText{ item->getName(), ui_->getFont(), 30 };
		conversationText.setPosition(position_ + sf::Vector2f(80.0f, 82.0f + 52.0f * i));
		conversationText.setColor(sf::Color::Black);
		window.draw(conversationText);
	}
}

/*
* FUNKTION UIInventoryFrame::handleKeyEvent(const sf::Event& ev)
*
* BESKRIVNING
*
* Hanterar tangentbordshändelser.
*
* INDATA
*
* ev:	Händelse som ska behandlas.
*
* UTDATA
*
* -
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

void UIInventoryFrame::handleKeyEvent(const	sf::Event& ev)
{
	switch (ev.key.code)
	{
	case sf::Keyboard::L:
		toggleVisible();
		break;
	}
}

/*
* SLUT PÅ FILEN UIInventoryFrame.cpp
*/