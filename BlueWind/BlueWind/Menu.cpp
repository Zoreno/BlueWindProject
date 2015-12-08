#include "Menu.h"
#include "Application.h"
#include "GameOver.h"
#include "Help.h"
#include <iostream>

using namespace std;

Menu::Menu(Application * appPtr)
	: Frame{appPtr} 
{
	void newGameCallback(Application*);
	void loadGameCallback(Application*);
	void quitCallback(Application*);
	void helpCallback(Application*);
	void creditsCallback(Application*);
	addButton(sf::Vector2f(400-175, 150), sf::Vector2f(350, 100), "res/textures/newgameButton.png", "res/textures/newgameButtonHover.png", newGameCallback);
	addButton(sf::Vector2f(400 - 175, 275), sf::Vector2f(350, 100), "res/textures/loadgameButton.png", "res/textures/loadgameButtonHover.png", loadGameCallback);
	addButton(sf::Vector2f(400 - 175, 400), sf::Vector2f(350, 100), "res/textures/quitButton.png", "res/textures/quitButtonHover.png", quitCallback);
	addButton(sf::Vector2f(800 - 155, 600 - 65), sf::Vector2f(130, 50), "res/textures/helpButton.png", "res/textures/helpButtonHover.png", helpCallback);
	addButton(sf::Vector2f(25, 600 - 65), sf::Vector2f(130, 50), "res/textures/creditsButton.png", "res/textures/creditsButtonHover.png", creditsCallback);
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
		sf::Vector2i mousePosition{ appPointer_->getGameWindow().mapPixelToCoords(sf::Mouse::getPosition(appPointer_->getGameWindow())) };
		for (auto it : buttons_)
		{
			if (it->mouseOnButton(mousePosition))
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
	sf::Texture bTexture;
	if (!bTexture.loadFromFile("res/textures/Menu.png"))
		throw FrameException("Kunde inte läsa in bild för Menu: res/textures/Menu.png");

	background_.setTexture(bTexture);
	window.draw(background_);

	for (auto it : buttons_)
	{
		it->render(window);
	}
}

void newGameCallback(Application* ptr)
{
	ptr->setNextFrame(new Game(ptr));
}

void loadGameCallback(Application* ptr)
{
	ptr->setNextFrame(new Game(ptr, true));
}

void quitCallback(Application* ptr)
{
	ptr->getGameWindow().close();
}

void helpCallback(Application* ptr)
{
	ptr->setNextFrame(new Help(ptr)); 
}

void creditsCallback(Application* ptr)
{
	ptr->getGameWindow().close(); // TODO Byt!
}

