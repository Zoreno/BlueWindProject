#include "Menu.h"
#include <iostream>

using namespace std;

Menu::Menu(Application * appPtr)
	: Frame{appPtr} 
{
	

	addButton(sf::Vector2f(385, 285), "res/textures/Startbutton.png");
	addButton(sf::Vector2f(385, 385), "res/textures/Startbutton.png");
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
	sf::Texture bTexture;

	if (!bTexture.loadFromFile("res/textures/Menu.png"))
		cout << "Could not load menu" << endl;

	background_.setTexture(bTexture);

	window.draw(background_);

	//Render komponenter
	for (auto it : buttons_)
	{
		it->render(window);
	}
}
