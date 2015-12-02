#include "TextureHandler.h"
#include <iostream>

using namespace std;

TextureHandler::TextureHandler()
{
	cout << "Laddar texturer" << endl;
	loadTexture("grass", "res/textures/Gräs.png");
	loadTexture("tree", "res/textures/Gran.png");
	loadTexture("bridge", "res/textures/bridge.png");
	loadTexture("player", "res/textures/enemy2.png");
	loadTexture("enemy", "res/textures/enemy1.png"); 
	loadTexture("NPC", "res/textures/player/playerHEj.png");
	cout << "Laddar texturer klart" << endl;
}

TextureHandler::~TextureHandler()
{
	while (!textures_.empty())
	{
		auto it = textures_.begin();
		delete it->second;
		textures_.erase(it);
	}
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
