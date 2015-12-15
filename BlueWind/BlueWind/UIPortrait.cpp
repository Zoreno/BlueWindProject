/*
* IDENTIFIERING
*
* Filnamn:    UIPortrait.cpp
* Enhetsnamn: UIPortrait
* Typ:        Definitioner hörande till klass UIPortrait
* Revision:   1
* Skriven av: Joakim Bertils, Johannes Grundell
*
*
* BESKRIVNING
*
* Denna implementeringsfil definierar medlemsfunktioner för klassen UIPortrait
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

#include "UIPortrait.h"
#include <string>

using namespace std;

/*
* KONSTRUKTOR UIPortrait(UserInterface * uiPtr, Player * playerPtr)
*
* BESKRIVNING
*
* Denna konstruktor konstruerar en ruta som visar spelarens attribut.
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
* modul:	UIBar
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

UIPortrait::UIPortrait(UserInterface * uiPtr, Player * playerPtr)
	:UIComponent{ sf::Vector2f(10,10), sf::Vector2f(200,120), uiPtr, playerPtr },
	healthBar_{position_ + sf::Vector2f(10,40), sf::Vector2f(180,20), sf::Color::Red, "HP", uiPtr},
	manaBar_{ position_ + sf::Vector2f(10,60), sf::Vector2f(180,20), sf::Color::Yellow, "kWh", uiPtr },
	expBar_{ position_ + sf::Vector2f(10,80), sf::Vector2f(180,20), sf::Color::Green, "XP", uiPtr }
{
}

/*
* FUNKTION UIPortrait::handleKeyEvent(const sf::Event& ev)
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

void UIPortrait::handleKeyEvent(const sf::Event&)
{
}

/*
* FUNKTION UIPortrait::update()
*
* BESKRIVNING
*
* Uppdaterar attributrutan
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

void UIPortrait::update()
{
	healthBar_.update(player_->getHealth(), player_->getMaxHealth());
	manaBar_.update(player_->getMana(), player_->getMaxMana());
	expBar_.update(player_->getExperience(), player_->getMaxExperience());
}

/*
* FUNKTION UIPortrait::render(GameWindow & window)
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
* SIDOEFFEKTER
*
* -
*
* UTNYTTJAR
*
* modul:	sfml-grafik
* modul:	UIBar
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

void UIPortrait::render(GameWindow & window)
{
	sf::RectangleShape frame{ size_ };
	frame.setPosition(position_);
	frame.setFillColor(sf::Color{ 200,200,200,100 });
	frame.setOutlineColor(sf::Color{ 100,100,100,255 });
	frame.setOutlineThickness(4.0f);
	window.draw(frame);

	sf::Text nameText{ player_->getName() + "  " + to_string(player_->getLevel()), ui_->getFont(), 30 };
	nameText.setPosition(position_ + sf::Vector2f(10,0));
	nameText.setColor(sf::Color::Black);
	window.draw(nameText);

	healthBar_.render(window);
	manaBar_.render(window);
	expBar_.render(window);

}

/*
* SLUT PÅ FILEN UIPortrait.cpp
*/