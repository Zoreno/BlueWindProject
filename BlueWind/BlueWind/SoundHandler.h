#pragma once

#include <map>
#include <string>
#include <SFML/Audio.hpp>

using soundTable = std::map<const std::string, sf::SoundBuffer*>;
using musicTable = std::map<const std::string, sf::Music*>;

class SoundHandler
{
public:
	SoundHandler();
	SoundHandler(const SoundHandler&) = delete;
	SoundHandler& operator=(const SoundHandler&) = delete;

	//TODO destruktor

	sf::SoundBuffer& getSound(const std::string&);
	sf::Music& getMusic(const std::string&);

	void playSound(const std::string&);
	void playMusic(const std::string&);
	void stopMusic(const std::string&);
	
private:
	soundTable sounds_;
	musicTable music_;
	sf::Sound currentSound_;

	void loadSound(const std::string&, const std::string&);
	void loadMusic(const std::string&, const std::string&);
};
