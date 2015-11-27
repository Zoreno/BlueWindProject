#include "Game.h"
#include <iostream>

using namespace std;

Game::Game(Application * appPtr)
	:Frame{appPtr}, universe_{this}, player_{universe_.getCurrentWorld(), textureHandler_.getTextureRef("player"), this, "res/textures/player/player32.png" }, ui_{&player_}
{
	cout << "Game startas!" << endl;
}

void Game::update()
{
	//cout << "Game uppdaterar" << endl;
	universe_.update();
	player_.update();
	ui_.update();
}

void Game::render(GameWindow & window)
{
	sf::View view2 = window.getView();
	view2.setCenter(player_.getPosition());
	window.setView(view2);
	//cout << "Game renderar" << endl;
	universe_.render(window);
	player_.render(window);
	ui_.render(window);
}

void Game::handleKeyEvent(sf::Event event)
{
	switch (event.key.code)
	{
	case sf::Keyboard::Space:
		player_.attack(universe_.getCurrentWorld()->getEnemyVector());
		
		break;
	case sf::Keyboard::I:

		//TODO flytta in i player kanske
		for (auto it : universe_.getCurrentWorld()->getNPCVector())
		{
			if (getDistance(player_.getPosition(), it.second->getPosition()) <= 32)
			{
				it.second->interact();
				break;
			}
		}
		break;
	case sf::Keyboard::U:
		cout << (int) player_.getPosition().x / 32 << "," << (int) player_.getPosition().y / 32 << endl;
		break;
	case sf::Keyboard::L:
		ui_.addStringToChatBox("Hejsan.!");
		break;
	case sf::Keyboard::E:
	case sf::Keyboard::T:
		ui_.handleKeyEvent(event);
		break;
	default:
		break;
	}
	
}

void Game::handleMouseEvent(sf::Event)
{
}

Player * Game::getPlayer()
{
	return &player_;
}

Application * Game::getApp()
{
	return appPointer_;
}

UserInterface * Game::getUserInterface()
{
	return &ui_;
}

sf::Texture & Game::getTexture(const std::string& ref)
{
	return textureHandler_.getTextureRef(ref);
}

