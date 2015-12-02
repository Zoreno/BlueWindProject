#include "TextureHandler.h"
#include <iostream>

using namespace std;

TextureHandler::TextureHandler()
{
	cout << "Laddar texturer" << endl;
	loadTexture("grass", "res/textures/Gräs.png");
	loadTexture("tree", "res/textures/Gran.png");
	loadTexture("bridge", "res/textures/bridge.png");
	loadTexture("house00", "res/textures/house00.png");
	loadTexture("house10", "res/textures/house10.png");
	loadTexture("house01", "res/textures/house01.png");
	loadTexture("house11", "res/textures/house11.png");
	loadTexture("mountainGrass", "res/textures/mountainGrass.png");
	loadTexture("water", "res/textures/water.png");
	loadTexture("stump", "res/textures/stump.png");
	loadTexture("player", "res/textures/player/playerHEj.png");
	loadTexture("enemy", "res/textures/player/playerHEj.png"); 
	loadTexture("NPC", "res/textures/player/playerHEj.png");
	cout << "Laddar texturer klart" << endl;
}

sf::Texture & TextureHandler::getTextureRef(const std::string& ref)
{
	return (*textures_.find(ref)->second);
}

void TextureHandler::loadTexture(const std::string& texName, const std::string& fileName)
{
	sf::Texture* tex = new sf::Texture;
	if (!tex->loadFromFile(fileName))
	{
		//TODO lägg till ex
		cout << "Kan inte ladda textur: " + texName << endl;
	}
	textures_.emplace(texName, tex);
}
