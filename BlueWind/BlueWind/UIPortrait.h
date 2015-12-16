/*
* IDENTIFIERING
*
* Filnamn:    UIInventoryFrame.h
* Enhetsnamn: UIInventoryFrame
* Typ:        Moduldeklaration
* Revision:   1
* Skriven av: Joakim Bertils, Johannes Grundell
*
*
* BESKRIVNING
*
* Denna modul representerar en ruta på användargränssnittet som visar
* spelarens attribut.
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

#include "UIComponent.h"
#include "UIBar.h"
#include "UserInterface.h"

/*
* KLASS UIPortrait
*
* BASKLASSER
*
* UIComponent
*
* BESKRIVNING
*
* Klassen representerar en ruta på användargränssnittet som visar
* spelarens attribut.
*
* TILLSTÅND
*
* -
*
* KONSTRUKTORER
*
* UIPortrait(UserInterface * uiPtr, Player * playerPtr)
*
* OPERATIONER
*
* -
*
* DATAMEDLEMMAR
*
* healthBar_:	Mätarobjekt som visar spelarens hälsa.
* manaBar_:		Mätarobjekt som visar spelarens energi.
* expBar_:		Mätarobjekt som visar spelarens erfarenhet.
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151120  Ursprungsversion
*
*/

class UIPortrait : public UIComponent
{
public:
	UIPortrait(UserInterface*, Player*);
	UIPortrait() = delete;
	UIPortrait(const UIPortrait&) = delete;
	UIPortrait& operator=(const UIPortrait&) = delete;

	void handleKeyEvent(const sf::Event&) override;
	void update() override;
	void render(GameWindow&) override;

private:
	UIBar healthBar_;
	UIBar manaBar_;
	UIBar expBar_;
};//class UIInventoryFrame

/*
 * SLUT PÅ FILEN UIÍnventoryFrame.h
 */