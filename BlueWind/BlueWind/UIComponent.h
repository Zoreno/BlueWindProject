/*
* IDENTIFIERING
*
* Filnamn:    UIComponent.h
* Enhetsnamn: UIComponent
* Typ:        Moduldeklaration
* Revision:   1
* Skriven av: Joakim Bertils, Johannes Grundell
*
*
* BESKRIVNING
*
* Denna modul representerar en komponent på användargränssnittet.
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
#include "Player.h"

/*
* FRAMÅTDEKLARATIONER
*/

class UserInterface;

/*
* KLASS UIComponent
*
* BASKLASSER
*
* -
*
* BESKRIVNING
*
* Klassen representerar en komponent på användargränssnittet.
*
* TILLSTÅND
*
* -
*
* KONSTRUKTORER
*
* UIComponent(sf::Vector2f position, sf::Vector2f size, UserInterface * uiPtr, Player * playerPtr, bool visible)
*
* OPERATIONER
*
* -
*
* DATAMEDLEMMAR
*
* sf::Vector2f position_;
* sf::Vector2f size_;
* UserInterface* ui_;
* Player* player_;
* bool visible_;
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151120  Ursprungsversion
*
*/

class UIComponent
{
public:
	UIComponent(sf::Vector2f, sf::Vector2f, UserInterface*, Player*, bool = true);
	UIComponent() = delete;
	UIComponent(const UIComponent&) = delete;
	UIComponent& operator=(const UIComponent&) = delete;

	virtual void handleKeyEvent(const sf::Event&) = 0;
	virtual void update() = 0;
	virtual void render(GameWindow&) = 0;

	bool isVisible() const;
	sf::Vector2f getPosition() const;
	void toggleVisible();
	void setVisible(bool);
protected:
	sf::Vector2f position_;
	sf::Vector2f size_;
	UserInterface* ui_;
	Player* player_;
	bool visible_;
};//class UIBar

/*
* SLUT PÅ FILEN UIBar.h
*/
