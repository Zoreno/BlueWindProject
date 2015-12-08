#include "Help.h"
#include "Application.h"
#include <iostream>

using namespace std;

Help::Help(Application * appPtr)
	: Frame{ appPtr }
{
	void helpMenuCallback(Application*);
	addButton(sf::Vector2f(400 - 175, 365), sf::Vector2f(350, 100), "res/textures/menuButton.png", "res/textures/menuButtonHover.png", helpMenuCallback);
}



void Help::handleKeyEvent(sf::Event event)
{
}

void Help::handleMouseEvent(sf::Event event)
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

void Help::update()
{
	for (auto it : buttons_)
	{
		it->update();
	}
}

void Help::render(GameWindow & window)
{
	sf::Texture bTexture;
	if (!bTexture.loadFromFile("res/textures/help.png"))
		throw FrameException("Kunde inte läsa in bild för Help: res/textures/help.png");

	background_.setTexture(bTexture);
	window.draw(background_);

	for (auto it : buttons_)
	{
		it->render(window);
	}
}

void helpMenuCallback(Application* ptr)
{
	ptr->setNextFrame(new Menu(ptr));
}

