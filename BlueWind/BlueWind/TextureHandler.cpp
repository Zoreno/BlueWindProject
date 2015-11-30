#include "TextureHandler.h"
#include <iostream>

using namespace std;

TextureHandler::TextureHandler()
{
	cout << "Laddar texturer" << endl;
	loadTexture("grass", "res/textures/Gräs.png");
	loadTexture("tree", "res/textures/Gran.png");
	loadTexture("bridge", "res/textures/bridge.png");
	loadTexture("player", "res/textures/player32.png");
	loadTexture("enemy", "res/textures/enemy.png"); 
	loadTexture("NPC", "res/textures/NPC.png");
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
