#include "UserInterface.h"

void UserInterface::update()
{
	for (auto it : components_)
	{
		it->update();
	}
}

void UserInterface::render(GameWindow & window)
{
	for (auto it : components_)
	{
		if (it->isVisible())
		{
			it->render(window);
		}
	}
}

void UserInterface::loadComponents()
{
}
