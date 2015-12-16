/* IDENTIFIERING
*
* Filnamn:    NPC.h
* Enhetsnamn: NPC
* Typ:        Moduldeklaration
* Revision:   1
* Skriven av: Simon Arkeholt, Fredrik Gustafsson
*
*
* BESKRIVNING
*
* Denna modul representerar en NPC i spelet.
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151214  Ursprungsversion
*
*/

#pragma once

/*
* REFERERADE BIBLIOTEK OCH MODULER
*/

#include <functional>
#include "Entity.h"
#include "GameWindow.h"

/*
* KLASS NPC
*
* BASKLASSER
*
* Entity
*
* BESKRIVNING
*
* Klassen representerar en NPC i spelet.
*
* KONSTRUKTORER
*
* NPC(int, int, int, int, std::string, sf::Vector2f, World*, sf::Texture&, std::string, std::function<void(NPC*)>)
*
* DATAMEDLEMMAR
*
* sprite_:			Anger NPC:ns sprite.
* conversation_:	Anger NPC:ns konversation.
* callback_:		NPC:ns callbackfunktion.
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151214  Ursprungsversion
*
*/

class NPC : public Entity
{
public:
	NPC(int, int, int, int, std::string, sf::Vector2f, World*, sf::Texture&, std::string, std::function<void(NPC*)>);
	NPC() = delete;
	NPC(const NPC&) = delete;
	NPC& operator=(const NPC&) = delete;

	void update() override;
	void render(GameWindow&) override;
	void talk() const;
	void interact();

	void die() override;
private:
	sf::Sprite sprite_;
	std::string conversation_;
	std::function<void(NPC*)> callback_;
}; 

/*
* SLUT PÅ FILEN NPC.h
*/