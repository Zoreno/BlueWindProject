#include "SoundHandler.h"
#include <iostream>

using namespace std;

SoundHandler::SoundHandler()
{
	cout << "Laddar ljud" << endl;
	loadMusic("menuMusic", "res/sounds/menuMusic.ogg");
	loadSound("menuClick", "res/sounds/menuClick.wav");
	cout << "Laddar ljud klart" << endl;
}

sf::Sound& SoundHandler::getSound(const std::string& soundName)
{
	return (*sounds_.find(soundName)->second);
}


sf::Music& SoundHandler::getMusic(const std::string& musicName)
{
	return (*music_.find(musicName)->second);
}

void SoundHandler::loadSound(const std::string& soundName, const std::string& fileName)
{
	sf::SoundBuffer soundBuffer;
	sf::Sound* sound = new sf::Sound;
	if (!soundBuffer.loadFromFile(fileName))
	{
		//TODO lägg till ex
		cout << "Kan inte ladda ljud: " + soundName << endl;
	}
	sound->setBuffer(soundBuffer);
	sounds_.emplace(soundName, sound);
}

void SoundHandler::loadMusic(const std::string& musicName, const std::string& fileName)
{
	sf::Music* music = new sf::Music;
	if (!music->openFromFile(fileName))
	{
		//TODO lägg till ex
		cout << "Kan inte ladda musik: " + musicName << endl;
	}
	music_.emplace(musicName, music);
}

