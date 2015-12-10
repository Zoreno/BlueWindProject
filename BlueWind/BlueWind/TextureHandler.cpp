#include "TextureHandler.h"
#include <iostream>

using namespace std;

TextureHandler::TextureHandler()
{
	cout << "Laddar texturer" << endl;

	loadTexture("void", "res/textures/voidtile.png");

	//Tiles
	loadTexture("grass", "res/textures/grass.png");
	loadTexture("grassTree", "res/textures/grassTree.png");
	loadTexture("bridge", "res/textures/bridge.png");
	loadTexture("mountainGrass", "res/textures/mountainGrass.png");
	loadTexture("water", "res/textures/water.png");
	loadTexture("snow", "res/textures/snow.png");
	loadTexture("snowTree", "res/textures/snowTree.png");
	loadTexture("snowChest", "res/textures/snowChest.png");
	loadTexture("grassStump", "res/textures/grassStump.png");
	loadTexture("sand", "res/textures/sand.png");
	loadTexture("palmtree", "res/textures/palmtree.png");
	loadTexture("cactus", "res/textures/cactus.png");
	loadTexture("lava", "res/textures/lava.png");
	loadTexture("burnedTree", "res/textures/burnedTree.png");
	loadTexture("lavastone", "res/textures/lavastone.png");
	loadTexture("grassBurnedTree", "res/textures/grassBurnedTree.png");


	//Items
	loadTexture("grassTreeChoppable", "res/textures/grassTreeChoppable.png");
	loadTexture("pickAxe", "res/textures/pickAxe.png");
	loadTexture("energyRing", "res/textures/energyRing.png");
	loadTexture("armour", "res/textures/armour.png");
	loadTexture("sword", "res/textures/sword.png");
	loadTexture("magicFireOrb", "res/textures/magicFireOrb.png");

	//Player
	loadTexture("player", "res/textures/player.png");

	//Enemies
	loadTexture("enemy", "res/textures/enemy7.png"); 
	loadTexture("enemy1", "res/textures/enemy1.png");
	loadTexture("ghost", "res/textures/enemy3.png");
	loadTexture("enemy4", "res/textures/enemy4.png");
	loadTexture("enemy7", "res/textures/enemy7.png");
	loadTexture("blueWind", "res/textures/blueWind.png");
	loadTexture("wizzzard", "res/textures/figur5.png");
	loadTexture("blueWizard", "res/textures/blueWizard.png");
	loadTexture("badAlloc", "res/textures/badAlloc.png");
	loadTexture("snowWolf", "res/textures/snowWolf.png");
	loadTexture("fire", "res/textures/fire.png");

	//NPC
	loadTexture("NPC", "res/textures/NPC1.png");
	loadTexture("NPC1", "res/textures/NPC1.png");
	loadTexture("NPC2", "res/textures/NPC2.png");
	loadTexture("NPC3", "res/textures/NPC3.png");
	loadTexture("NPC4", "res/textures/NPC4.png");
	loadTexture("NPC5", "res/textures/NPC5.png");
	loadTexture("NPC6", "res/textures/NPC6.png");
	loadTexture("NPC7", "res/textures/NPC7.png");
	loadTexture("NPC8", "res/textures/NPC8.png");
	loadTexture("saveNPC", "res/textures/saveNPC.png");
	loadTexture("Firimaniums", "res/textures/Firimaniums.png"); 


	//House
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
		throw TextureException("Kunde inte ladda in textur från fil:" + fileName);
	}
	textures_.emplace(texName, tex);
}
