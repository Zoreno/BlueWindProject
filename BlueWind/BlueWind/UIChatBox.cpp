/*
* IDENTIFIERING
*
* Filnamn:    UIChatBox.cpp
* Enhetsnamn: UIChatBox
* Typ:        Definitioner hörande till klass UIChatBox
* Revision:   1
* Skriven av: Joakim Bertils, Johannes Grundell
*
*
* BESKRIVNING
*
* Denna implementeringsfil definierar medlemsfunktioner för klassen UIChatBox.
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

#include "UIChatBox.h"
#include <iostream>

using namespace std;

/*
* KONSTRUKTOR UIChatBox(UserInterface* uiPtr, Player* playerPtr)
*
* BESKRIVNING
*
* Denna konstruktor konstruerar en mätare.
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
* 1                    151120          Ursprungsversion
*
*/

UIChatBox::UIChatBox(UserInterface* uiPtr, Player* playerPtr)
	:UIComponent{ sf::Vector2f(10,450), sf::Vector2f(300,100), uiPtr, playerPtr }
{}

/*
* FUNKTION UIChatBox::handleKeyEvent(sf::Event ev)
*
* BESKRIVNING
*
* Hanterar tangenthändelser.
*
* INDATA
*
* ev:	Eventobjekt som ska behandlas
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
* 1                    151120          Ursprungsversion
*
*/

void UIChatBox::handleKeyEvent(sf::Event ev) {}

/*
* FUNKTION UIChatBox::update()
*
* BESKRIVNING
*
* Uppdaterar textrutan.
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
* 1                    151120          Ursprungsversion
*
*/

void UIChatBox::update()
{
	if (inputBuffer_.size() > 4)
	{
		inputBuffer_.pop_back();
	}
}

/*
* FUNKTION UIChatBox::render(GameWindow & window)
*
* BESKRIVNING
*
* Ritar upp textrutan på fönstret window.
*
* INDATA
*
* window:	Fönster som textrutan ska ritas på.
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
* 1                    151120          Ursprungsversion
*
*/

void UIChatBox::render(GameWindow & window)
{
	sf::RectangleShape frame{ size_ };
	frame.setPosition(position_);
	frame.setFillColor(sf::Color{ 200,200,200,150 });
	frame.setOutlineColor(sf::Color{ 100,100,100,255 });
	frame.setOutlineThickness(4.0f);
	window.draw(frame);

	for (int i{ 0 }; i < (min(4, (int)inputBuffer_.size())); ++i)
	{
		sf::Text conversationText{ inputBuffer_.at(i), ui_->getFont(), 20 };
		conversationText.setPosition(position_ + sf::Vector2f(0, 24.0f*(3 - i)));
		conversationText.setColor(sf::Color::Black);
		window.draw(conversationText);
	}
}

/*
* FUNKTION UIChatBox::setConversation(const std::string& newConversation)
*
* BESKRIVNING
*
* Lägger till en textsträng i textrutan. Om textsträngen börjar med en '*' kommer
* bufferten att tömmas innan insättning.
*
* INDATA
*
* newConversation:	textsträng som ska sättas in
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
* 1                    151120          Ursprungsversion
*
*/

void UIChatBox::setConversation(const std::string& newConversation)
{
	if (newConversation.at(0) == '*')
	{
		inputBuffer_.clear();
		inputBuffer_.push_front(newConversation.substr(1, newConversation.length() - 1));
		return;
	}
	inputBuffer_.push_front(newConversation);
}

/*
* SLUT PÅ FILEN UIChatBox.cpp
*/