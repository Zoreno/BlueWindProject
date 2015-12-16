/*
* IDENTIFIERING
*
* Filnamn:    UserInterface.cpp
* Enhetsnamn: UserInterface
* Typ:        Definitioner hörande till klass Inventory
* Revision:   1
* Skriven av: Joakim Bertils, Johannes Grundell
*
*
* BESKRIVNING
*
* Denna implementeringsfil definierar medlemsfunktioner för klassen UserInterface.
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

#include "UserInterface.h"
#include "UIPortrait.h"
#include "UIChatBox.h"
#include "UIInventoryFrame.h"

using namespace std;

/*
* KONSTRUKTOR UserInterface::UserInterface(Player * playerPtr)
*
* BESKRIVNING
*
* Denna konstruktor konstruerar ett användagränssnitt.
*
* INDATA
*
* playerPtr:	Pekare till spelaren.
* gamePtr:		Pekare till spelframe.
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
* std::map
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

UserInterface::UserInterface(Player * playerPtr)
{
	if (!uiFont_.loadFromFile("res/calibri.ttf"))
	{
		throw UIException("Kan inte läsa in typsnitt: res/calibri.ttf");
	}
	loadComponents(playerPtr);
}

/*
* DESTRUKTOR UserInterface::~UserInterface()
*
* BESKRIVNING
*
* Denna destruktor destrukterar ett användargränssnitt.
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
* std::map
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

UserInterface::~UserInterface()
{
	while (!components_.empty())
	{
		auto it = components_.begin();
		delete it->second;
		components_.erase(it);
	}
}

/*
* FUNKTION UserInterface::handleKeyEvent(const sf::Event& ev)
*
* BESKRIVNING
*
* Hanterar knapp-event i användargränssnittet.
*
* INDATA
*
* ev:		Eventet som ska hanteras.
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
* modul: std::map
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

void UserInterface::handleKeyEvent(const sf::Event& ev)
{
	for (auto it : components_)
	{
		it.second->handleKeyEvent(ev);
	}
}

/*
* FUNKTION UserInterface::addStringToChatBox(std::string newString)
*
* BESKRIVNING
*
* Lägger till en sträng till användargränssnittets chattruta.
*
* INDATA
*
* newString:	Strängen som ska läggas till.
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
* modul: std::map
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

void UserInterface::addStringToChatBox(std::string newString)
{
	dynamic_cast<UIChatBox*>(components_.at("chatbox"))->setConversation(newString);
}

/*
* FUNKTION UserInterface::update()
*
* BESKRIVNING
*
* Uppdaterar användargränssnittet.
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
* modul: std::map
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

void UserInterface::update()
{
	for (auto it : components_)
	{
		it.second->update();
	}
}

/*
* FUNKTION UserInterface::render(GameWindow & window)
*
* BESKRIVNING
*
* Renderar användargränssnittet på fönstret.
*
* INDATA
*
* window:		Fönstret som användargränssnittet renderas i.
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
* modul: std::map
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

void UserInterface::render(GameWindow & window)
{
	sf::View old = window.getView();
	window.setView(uiView_);
	for (auto it : components_)
	{
		if (it.second->isVisible())
		{
			it.second->render(window);
		}
	}
	window.setView(old);
}

/*
* FUNKTION UserInterface::getFont()
*
* BESKRIVNING
*
* Returnerar en referens till användargränssnittets typsnitt.
*
* INDATA
*
* -
*
* UTDATA
*
* sf::Font&:		Användargränssnittets typsnitt.
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

sf::Font & UserInterface::getFont()
{
	return uiFont_;
}

/*
* FUNKTION UserInterface::loadComponents(Player* playerPtr)
*
* BESKRIVNING
*
* Lägger till komponenter på användargränssnittet.
*
* INDATA
*
* playerPtr:		Pekare till spelaren.
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
* modul: std::map
*
* REVISIONSBERÄTTELSE
*
* Revision             Datum           Förändringar
*
* 1                    151120          Ursprungsversion
*
*/

void UserInterface::loadComponents(Player* playerPtr)
{
	components_.emplace("portrait", new UIPortrait(this, playerPtr));
	components_.emplace("chatbox", new UIChatBox(this, playerPtr));
	components_.emplace("inventoryScreen", new UIInventoryFrame(this, playerPtr));
}

/*
* SLUT PÅ FILEN UserInterface.cpp
*/