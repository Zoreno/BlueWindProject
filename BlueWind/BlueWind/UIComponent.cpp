/*
* IDENTIFIERING
*
* Filnamn:    UIComponent.cpp
* Enhetsnamn: UIComponent
* Typ:        Definitioner hörande till klass UIComponent
* Revision:   1
* Skriven av: Joakim Bertils, Johannes Grundell
*
*
* BESKRIVNING
*
* Denna implementeringsfil definierar medlemsfunktioner för klassen UIComponent
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

#include "UIComponent.h"

/*
* KONSTRUKTOR UIComponent(sf::Vector2f position, sf::Vector2f size, UserInterface * uiPtr, Player * playerPtr, bool visible)
*
* BESKRIVNING
*
* Denna konstruktor konstruerar en komponent på användargränssnittet.
*
* INDATA
*
* position:		Plats på skärm där mätaren ska ritas.
* size:			Storlek på mätaren.
* uiPtr:		Pekare till användargränssnittet som mätaren är en del av.
* playerPtr:	Pekare till spelaren.
* visible:		Anger om komponenten ska ritas.
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

UIComponent::UIComponent(sf::Vector2f position, sf::Vector2f size, UserInterface * uiPtr, Player * playerPtr, bool visible)
	:position_{position}, 
	size_{size}, 
	ui_{uiPtr}, 
	player_{playerPtr}, 
	visible_{visible}
{}

/*
* FUNKTION UIComponent::isVisible() const
*
* BESKRIVNING
*
* Returnerar sant om komponenten är synlig för användaren.
*
* INDATA
*
* -
*
* UTDATA
*
* bool:	Komponentens synlighetsstatus.
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

bool UIComponent::isVisible() const
{
	return visible_;
}

/*
* FUNKTION UIComponent::getPosition() const
*
* BESKRIVNING
*
* Returnerar komponentens position (övre vänstra hörn).
*
* INDATA
*
* -
*
* UTDATA
*
* sf::Vector2f:	Vektor med komponentens position.
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

sf::Vector2f UIComponent::getPosition() const
{
	return position_;
}

/*
* FUNKTION UIComponent::toggleVisible()
*
* BESKRIVNING
*
* Växlar komponentens synlighetsstatus.
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

void UIComponent::toggleVisible()
{
	visible_ = !visible_;
}

/*
* FUNKTION UIComponent::setVisible(bool value)
*
* BESKRIVNING
*
* Sätter komponentens synlighetsstatus till value.
*
* INDATA
*
* value:	Statusen som synligheten sätts till.
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

void UIComponent::setVisible(bool value)
{
	visible_ = value;
}

/*
* SLUT PÅ FILEN UIComponent.cpp
*/