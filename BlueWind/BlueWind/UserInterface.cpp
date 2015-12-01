#include "UserInterface.h"
#include <iostream>
#include "UIPortrait.h"
#include "UIChatBox.h"
#include "UIInventoryFrame.h"

using namespace std;

UserInterface::UserInterface(Player * playerPtr)
{
	if (!uiFont_.loadFromFile("res/calibri.ttf"))
	{
		//TODO lägg till exception
		cout << "Kan inte läsa font" << endl;
	}
	loadComponents(playerPtr);
}

UserInterface::~UserInterface()
{
	while (!components_.empty())
	{
		auto it = components_.begin();
		delete it->second;
		components_.erase(it);
	}
}

void UserInterface::handleKeyEvent(sf::Event ev)
{
	for (auto it : components_)
	{
		it.second->handleKeyEvent(ev);
	}
}

void UserInterface::addStringToChatBox(std::string newString)
{
	dynamic_cast<UIChatBox*>(components_.at("chatbox"))->setConversation(newString);
}

void UserInterface::update()
{
	for (auto it : components_)
	{
		it.second->update();
	}
}

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

sf::Font & UserInterface::getFont()
{
	return uiFont_;
}

void UserInterface::loadComponents(Player* playerPtr)
{
	components_.emplace("portrait", new UIPortrait(this, playerPtr));
	components_.emplace("chatbox", new UIChatBox(this, playerPtr));
	components_.emplace("inventoryScreen", new UIInventoryFrame(this, playerPtr));
}
