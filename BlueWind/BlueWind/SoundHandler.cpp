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

sf::SoundBuffer& SoundHandler::getSound(const std::string& soundName)
{
	return (*sounds_.find(soundName)->second);
}


sf::Music& SoundHandler::getMusic(const std::string& musicName)
{
	return (*music_.find(musicName)->second);
}

void SoundHandler::playSound(const std::string& soundName)
{
	sf::Sound sound;
	sound.setBuffer(*sounds_.find(soundName)->second);
	sound.play();
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
		//TODO lägg till ex
		cout << "Kan inte ladda ljud: " + soundName << endl;
	}
	sounds_.emplace(soundName, soundBuffer);
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

