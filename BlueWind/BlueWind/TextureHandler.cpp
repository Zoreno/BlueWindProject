#include "TextureHandler.h"
#include <iostream>

using namespace std;

TextureHandler::TextureHandler()
{
	//loadTextures();
}

sf::Texture & TextureHandler::getTextureRef(const std::string& ref)
{
	return textures_.find(ref)->second;
}

void TextureHandler::loadTexture(const std::string& texName, const std::string& fileName)
{
	sf::Texture tex;
	if (!tex.loadFromFile(fileName))
	{
		//TODO lägg till ex
		cout << "Kan inte ladda textur: " + texName << endl;
	}
	textures_.emplace(texName, tex);
}
