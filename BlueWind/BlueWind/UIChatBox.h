/*
* IDENTIFIERING
*
* Filnamn:    UIChatBox.h
* Enhetsnamn: UIChatBox
* Typ:        Moduldeklaration
* Revision:   1
* Skriven av: Joakim Bertils, Johannes Grundell
*
*
* BESKRIVNING
*
* Denna modul representerar en mätare på användargränssnittet.
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
#include "UserInterface.h"
#include <deque>

/*
* KLASS UIChatBox
*
* BASKLASSER
*
* UIComponent
*
* BESKRIVNING
*
* Klassen representerar en textruta på användargränssnittet.
*
* TILLSTÅND
*
* -
*
* KONSTRUKTORER
*
* UIChatBox(UserInterface* uiPtr, Player* playerPtr)
*
* OPERATIONER
*
* -
*
* DATAMEDLEMMAR
*
* inputBuffer_:	Buffer där texten i rutan lagras.
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151120  Ursprungsversion
*
*/

class UIChatBox : public UIComponent
{
public:
	UIChatBox(UserInterface*, Player*);
	UIChatBox() = delete;
	UIChatBox(const UIChatBox&) = delete;
	UIChatBox& operator=(const UIChatBox&) = delete;

	void handleKeyEvent(const sf::Event&) override;
	void update() override;
	void render(GameWindow&) override;

	void setConversation(const std::string&);
private:
	std::deque<std::string> inputBuffer_;
}; //class UIChatBox

/*
 * SLUT PÅ FILEN UIChatBox.h
 */
