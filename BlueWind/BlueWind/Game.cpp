#include "Game.h"
#include <iostream>

using namespace std;


Game::Game(Application * appPtr)
	:Frame{appPtr}, universe_{this}
{
	cout << "Game startas!" << endl;
}

void Game::update()
{
	cout << "Game uppdaterar" << endl;
	universe_.update();
}

void Game::render(GameWindow & window)
{
	cout << "Game renderar" << endl;
	universe_.render(window);
}

sf::Texture & Game::getTexture(const std::string& ref)
{
	return textureHandler_.getTextureRef(ref);
}

