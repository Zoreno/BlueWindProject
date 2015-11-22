#include "Menu.h"
#include "Application.h"
#include <iostream>

using namespace std;

Menu::Menu(Application * appPtr)
	: Frame{appPtr} 
{
	void startCallback(Application*);
	void quitCallback(Application*);
	addButton(sf::Vector2f(400-125, 200), "res/textures/startButton.png", sf::Vector2f(250, 100), startCallback);
	addButton(sf::Vector2f(400 - 125, 350), "res/textures/quitButton.png", sf::Vector2f(250, 100), quitCallback);
	appPtr->getSoundHandler().getMusic("menuMusic").play();
}

void Menu::handleKeyEvent(sf::Event event)
{
}

void Menu::handleMouseEvent(sf::Event event)
{
	switch (event.mouseButton.button)
	{
	case sf::Mouse::Left:
	{
		sf::Vector2i mousePosition{ sf::Mouse::getPosition(appPointer_->getGameWindow())};
		
		for (auto it : buttons_)
		{
			if (mousePosition.x > it->getPosition().x && mousePosition.x < it->getPosition().x + it->getSize().x &&
				mousePosition.y > it->getPosition().y && mousePosition.y < it->getPosition().y + it->getSize().y)
			{
				it->clicked();
				break;
			}
		}
	}
		
	default:
		break;
	}
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

void startCallback(Application* ptr)
{
	ptr->startGame();
}

void quitCallback(Application* ptr)
{
	ptr->getGameWindow().close();
}

