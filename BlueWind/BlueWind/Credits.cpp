#include "Credits.h"
#include "Application.h"
#include <iostream>

using namespace std;

Credits::Credits(Application * appPtr)
	: Frame{ appPtr }
{
	void creditsMenuCallback(Application*);
	addButton(sf::Vector2f(25, 600 - 65), sf::Vector2f(130, 50), "res/textures/menuButtonSmall.png", "res/textures/menuButtonSmallHover.png", creditsMenuCallback);
}



void Credits::handleKeyEvent(sf::Event event)
{
}

void Credits::handleMouseEvent(sf::Event event)
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

void Credits::update()
{
	for (auto it : buttons_)
	{
		it->update();
	}
}

void Credits::render(GameWindow & window)
{
	sf::Texture bTexture;
	if (!bTexture.loadFromFile("res/textures/credits.png"))
		throw FrameException("Kunde inte läsa in bild för Credits: res/textures/credits.png");

	background_.setTexture(bTexture);
	window.draw(background_);

	for (auto it : buttons_)
	{
		it->render(window);
	}
}

void creditsMenuCallback(Application* ptr)
{
	ptr->setNextFrame(new Menu(ptr));
}

