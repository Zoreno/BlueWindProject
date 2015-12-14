/* IDENTIFIERING
*
* Filnamn:    NPC.cpp
* Enhetsnamn: NPC
* Typ:        Definitioner hörande till klass NPC
* Revision:   1
* Skriven av: Simon Arkeholt, Fredrik Gustafsson
*
*
* BESKRIVNING
*
* Denna implementeringsfil definierar medlemsfunktioner för klassen NPC.
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

#include "NPC.h"
#include "World.h"
#include "Universe.h"
#include "Game.h"

using namespace std;

/*
* KONSTRUKTOR NPC(int level, int health, int damage, int ID, std::string name, sf::Vector2f position, World * worldPtr, sf::Texture& texture, string conversation, std::function<void(NPC*)> callbackFunc)
*
* BESKRIVNING
*
* Denna konstruktor konstruerar en NPC.
*
* INDATA
*
* level:		NPC:ns level.
* health:		NPC:ns hälsa.
* damage:		NPC:ns skadeverkan.
* ID:			NPC:ns ID.
* name:			NPC:ns namn.
* position:		NPC:ns position.
* worldPtr:		pekare till NPC:ns värld.
* texture:		NPC:ns textur.
* conversation:	NPC:ns konversation.
* callbackFunc:	NPC:ns interaktionsfunktion.
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
* 1                    151214          Ursprungsversion
*
*/

NPC::NPC(int level, int health, int damage, int ID, std::string name, sf::Vector2f position, World * worldPtr, sf::Texture& texture, string conversation, std::function<void(NPC*)> callbackFunc)
	: Entity(level, health, damage, ID, name, position, worldPtr, texture), 
	conversation_{ conversation }, 
	callback_{ callbackFunc }
{
	sprite_.setOrigin(sf::Vector2f(0.0f, 0.0f));
	sprite_.setPosition(position);
	sprite_.setTexture(texture);
}

/*
* FUNKTION NPC::update()
*
* BESKRIVNING
*
* Uppdaterar NPC:n.
*
* INDATA
*
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
* 1                    151214          Ursprungsversion
*
*/

void NPC::update()
{
}

/*
* FUNKTION NPC::render(GameWindow & window)
*
* BESKRIVNING
*
* Ritar NPC:n.
*
* INDATA
*
* window:		Fönster som NPC:n ska ritas på.
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
* 1                    151214          Ursprungsversion
*
*/

void NPC::render(GameWindow & window)
{
	sprite_.setPosition(position_);
	window.draw(sprite_);
}

/*
* FUNKTION NPC::talk() const
*
* BESKRIVNING
*
* Lägger till NPC:ns konversation till chatboxen.
*
* INDATA
*
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
* 1                    151214          Ursprungsversion
*
*/

void NPC::talk() const
{
	if (conversation_.size() == 0) return;
	worldPointer_->getUniverse()->getGame()->getUserInterface()->addStringToChatBox(conversation_);
}

/*
* FUNKTION NPC::interact()
*
* BESKRIVNING
*
* Kallar på talk och NPC:ns callbackfunktion.
*
* INDATA
*
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
* 1                    151214          Ursprungsversion
*
*/

void NPC::interact()
{
	talk();
	callback_(this);
}

/*
* FUNKTION NPC::die()
*
* BESKRIVNING
*
* Tar bort NPC:n från spelvärlden.
*
* INDATA
*
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
* 1                    151214          Ursprungsversion
*
*/

void NPC::die()
{
	worldPointer_->removeNPC(this);
}

/*
* SLUT PÅ FILEN NPC.cpp
*/
