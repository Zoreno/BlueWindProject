#include "SoundHandler.h"
#include <iostream>

using namespace std;

SoundHandler::SoundHandler()
{
	cout << "Laddar ljud" << endl;
	loadMusic("menuMusic", "res/sounds/menuMusic.ogg");
	loadMusic("gameOverMusic", "res/sounds/gameOverMusic.ogg");
	loadMusic("gameWonMusic", "res/sounds/gameWonMusic.ogg");
	loadMusic("world0Music", "res/sounds/world0Music.ogg");
	loadMusic("world1Music", "res/sounds/world1Music.ogg");
	loadMusic("world2Music", "res/sounds/world2Music.ogg");
	loadMusic("world3Music", "res/sounds/world3Music.ogg");

	loadSound("menuClick", "res/sounds/menuClick.ogg");
	loadSound("diracTrain", "res/sounds/diracTrain.ogg");
	cout << "Laddar ljud klart" << endl;
}

SoundHandler::~SoundHandler()
{
	while (!sounds_.empty())
	{
		auto it = sounds_.begin();
		delete it->second;
		sounds_.erase(it);
	}

	while (!music_.empty())
	{
		auto it = music_.begin();
		delete it->second;
		music_.erase(it);
	}
}

void SoundHandler::playSound(const std::string& soundName)
{
	currentSound_.setBuffer(*sounds_.find(soundName)->second);
	currentSound_.play();
}

void SoundHandler::playMusic(const std::string& musicName)
{
	music_.find(musicName)->second->play();
	music_.find(musicName)->second->setLoop(true);
}

void SoundHandler::stopMusic(const std::string& musicName)
{
	music_.find(musicName)->second->stop();
}

void SoundHandler::loadSound(const std::string& soundName, const std::string& fileName)
{
	sf::SoundBuffer* soundBuffer = new sf::SoundBuffer;
	if (!soundBuffer->loadFromFile(fileName))
	{
		throw SoundException("Kunde inte ladda in ljud från fil:" + fileName);
	}
	sounds_.emplace(soundName, soundBuffer);
}

void SoundHandler::loadMusic(const std::string& musicName, const std::string& fileName)
{
	sf::Music* music = new sf::Music;
	if (!music->openFromFile(fileName))
	{
		throw SoundException("Kunde inte ladda in musik från fil:" + fileName);
	}
	music_.emplace(musicName, music);
}

