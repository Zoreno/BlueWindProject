#include "Menu.h"

Menu::Menu(Application * appPtr)
	: Frame{appPtr} 
{
	addButton(sf::Vector2f(200, 200), sf::Vector2f(200, 200), "Hejsan");
}

void Menu::update()
{
	for (auto it : buttons_)
	{
		it->update();
	}
}

void Menu::render(GameWindow & window)
{
	//Render bakgrund

	//Render komponenter
	for (auto it : buttons_)
	{
		it->render(window);
	}
}
