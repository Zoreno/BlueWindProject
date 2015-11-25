#include "SoundHandler.h"
#include <iostream>


using namespace std;

SoundHandler::SoundHandler()
{
	cout << "Laddar ljud" << endl;
	loadMusic("menuMusic", "res/sounds/menuMusic.ogg");
	loadSound("menuClick", "res/sounds/menuClick.ogg");
	loadSound("diracTrain", "res/sounds/diracTrain.ogg");
	cout << "Laddar ljud klart" << endl;
}

void SoundHandler::playSound(const std::string& soundName)
{
	currentSound_.setBuffer(*sounds_.find(soundName)->second);
	currentSound_.play();
}

void SoundHandler::playMusic(const std::string& musicName)
{
	(*music_.find(musicName)->second).play();
}

void SoundHandler::stopMusic(const std::string& musicName)
{
	(*music_.find(musicName)->second).stop();
}

void SoundHandler::loadSound(const std::string& soundName, const std::string& fileName)
{
	sf::SoundBuffer* soundBuffer = new sf::SoundBuffer;
	if (!soundBuffer->loadFromFile(fileName))
	{
		//TODO l�gg till ex
		cout << "Kan inte ladda ljud: " + soundName << endl;
	}
	sounds_.emplace(soundName, soundBuffer);
}

void SoundHandler::loadMusic(const std::string& musicName, const std::string& fileName)
{
	sf::Music* music = new sf::Music;
	if (!music->openFromFile(fileName))
	{
		//TODO l�gg till ex
		cout << "Kan inte ladda musik: " + musicName << endl;
	}
	music_.emplace(musicName, music);
}
