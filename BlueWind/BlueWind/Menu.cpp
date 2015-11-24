#include "Menu.h"
#include "Application.h"
#include <iostream>

using namespace std;

Menu::Menu(Application * appPtr)
	: Frame{appPtr} 
{
	void newGameCallback(Application*);
	void loadGameCallback(Application*);
	void quitCallback(Application*);
	addButton(sf::Vector2f(400-175, 150), sf::Vector2f(350, 100), "res/textures/newgameButton.png", "res/textures/newgameButtonHover.png", newGameCallback);
	addButton(sf::Vector2f(400 - 175, 275), sf::Vector2f(350, 100), "res/textures/loadgameButton.png", "res/textures/loadgameButtonHover.png", loadGameCallback);
	addButton(sf::Vector2f(400 - 175, 400), sf::Vector2f(350, 100), "res/textures/quitButton.png", "res/textures/quitButtonHover.png", quitCallback);
	appPtr->getSoundHandler().playMusic("menuMusic");
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
			if (it->mouseOnButton(mousePosition))
			{
				it->clicked();
				break;
			}
		}
	}
	break;
	// Test för uppspelning av ljud!
	case sf::Mouse::Right:
	{
		appPointer_->getSoundHandler().playSound("menuClick");
		cout << "test" << endl;
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
	sf::Texture bTexture;
	if (!bTexture.loadFromFile("res/textures/Menu.png"))
		cout << "Could not load menu" << endl;

	background_.setTexture(bTexture);
	window.draw(background_);

	for (auto it : buttons_)
	{
		it->render(window);
	}
}

void newGameCallback(Application* ptr)
{
	ptr->startNewGame();
}

void loadGameCallback(Application* ptr)
{

}

void quitCallback(Application* ptr)
{
	ptr->getGameWindow().close();
}

