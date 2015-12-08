#include "GameOver.h"
#include "Application.h"
#include <iostream>

using namespace std;

GameOver::GameOver(Application * appPtr)
	: Frame{ appPtr }
{
	void menuCallback(Application*);
	addButton(sf::Vector2f(400 - 175, 365), sf::Vector2f(350, 100), "res/textures/menuButton.png", "res/textures/menuButtonHover.png", menuCallback);
	appPtr->getSoundHandler().playMusic("gameOverMusic");
}



void GameOver::handleKeyEvent(sf::Event event)
{
}

void GameOver::handleMouseEvent(sf::Event event)
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

void GameOver::update()
{
	for (auto it : buttons_)
	{
		it->update();
	}
}

void GameOver::render(GameWindow & window)
{
	sf::Texture bTexture;
	if (!bTexture.loadFromFile("res/textures/GameOver.png"))
		throw FrameException("Kunde inte läsa in bild för GameOver: res/textures/GameOver.png");

	background_.setTexture(bTexture);
	window.draw(background_);

	for (auto it : buttons_)
	{
		it->render(window);
	}
}

void menuCallback(Application* ptr)
{
	ptr->getSoundHandler().stopMusic("gameOverMusic");
	ptr->getSoundHandler().playMusic("menuMusic");
	ptr->setNextFrame(new Menu(ptr));
}

