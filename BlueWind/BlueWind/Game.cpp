#include "Game.h"
#include <iostream>

using namespace std;


Game::Game(Application * appPtr)
	:Frame{appPtr}, universe_{this}, player_{universe_.getCurrentWorld(), textureHandler_.getTextureRef("player")}
{
	cout << "Game startas!" << endl;
}

void Game::update()
{
	//cout << "Game uppdaterar" << endl;
	universe_.update();
	player_.update();
}

void Game::render(GameWindow & window)
{
	sf::View view2 = window.getView();
	view2.setCenter(player_.getPosition());
	window.setView(view2);
	//cout << "Game renderar" << endl;
	universe_.render(window);
	player_.render(window);
}

Player * Game::getPlayer()
{
	return &player_;
}

sf::Texture & Game::getTexture(const std::string& ref)
{
	return textureHandler_.getTextureRef(ref);
}

