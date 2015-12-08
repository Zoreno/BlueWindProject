#include "TextureHandler.h"
#include <iostream>

using namespace std;

TextureHandler::TextureHandler()
{
	cout << "Laddar texturer" << endl;

	loadTexture("void", "res/textures/voidtile.png");

	loadTexture("grass", "res/textures/grass.png");
	loadTexture("grassTree", "res/textures/grassTree.png");
	loadTexture("grassTreeChoppable", "res/textures/grassTreeChoppable.png");
	loadTexture("bridge", "res/textures/bridge.png");
	loadTexture("house00", "res/textures/house00.png");
	loadTexture("house10", "res/textures/house10.png");
	loadTexture("house01", "res/textures/house01.png");
	loadTexture("house11", "res/textures/house11.png");
	loadTexture("mountainGrass", "res/textures/mountainGrass.png");
	loadTexture("water", "res/textures/water.png");
	loadTexture("snow", "res/textures/snow.png");
	loadTexture("stump", "res/textures/stump.png");
	loadTexture("player", "res/textures/PLAYER2.png");
	loadTexture("enemy", "res/textures/enemy7.png"); 
	loadTexture("NPC", "res/textures/NPC1.png");
	loadTexture("enemy1", "res/textures/enemy1.png"); 
	loadTexture("enemy2", "res/textures/enemy2.png");
	loadTexture("enemy3", "res/textures/enemy3.png");

	loadTexture("NPC1", "res/textures/NPC1.png");
	loadTexture("NPC2", "res/textures/NPC2.png");
	loadTexture("NPC3", "res/textures/NPC3.png");
	loadTexture("NPC4", "res/textures/NPC4.png");
	loadTexture("NPC5", "res/textures/NPC5.png");

	loadTexture("house00", "res/textures/house00.png");
	loadTexture("house01", "res/textures/house01.png");
	loadTexture("house02", "res/textures/house02.png");
	loadTexture("house03", "res/textures/house03.png");
	loadTexture("house10", "res/textures/house10.png");
	loadTexture("house11", "res/textures/house11.png");
	loadTexture("house12", "res/textures/house12.png");
	loadTexture("house13", "res/textures/house13.png");
	loadTexture("house20", "res/textures/house20.png");
	loadTexture("house21", "res/textures/house21.png");
	loadTexture("house22", "res/textures/house22.png");
	loadTexture("house23", "res/textures/house23.png");
	loadTexture("house30", "res/textures/house30.png");
	loadTexture("house31", "res/textures/house31.png");
	loadTexture("house32", "res/textures/house32.png");
	loadTexture("house33", "res/textures/house33.png");

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
