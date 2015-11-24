#include "UserInterface.h"
#include <iostream>
#include "UIPortrait.h"
#include "UIConversation.h"

using namespace std;

UserInterface::UserInterface(Player * playerPtr)
{
	cout << playerPtr->getName() << endl;
	if (!uiFont_.loadFromFile("res/calibri.ttf"))
	{
		//TODO lägg till exception
		cout << "Kan inte läsa font" << endl;
	}
	loadComponents(playerPtr);
}

void UserInterface::update()
{
	for (auto it : components_)
	{
		it->update();
	}
}

void UserInterface::render(GameWindow & window)
{
	sf::View old = window.getView();
	window.setView(uiView_);
	for (auto it : components_)
	{
		if (it->isVisible())
		{
			it->render(window);
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
	components_.push_back(new UIPortrait(this, playerPtr));
	components_.push_back(new UIConversation(this, playerPtr));
}
