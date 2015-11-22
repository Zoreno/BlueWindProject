#pragma once

#include <map>
#include <string>
#include <SFML/Audio.hpp>

using soundTable = std::map<const std::string, sf::Sound*>;
using musicTable = std::map<const std::string, sf::Music*>;

class SoundHandler
{
public:
	SoundHandler();
	SoundHandler(const SoundHandler&) = delete;
	SoundHandler& operator=(const SoundHandler&) = delete;

	//TODO destruktor

	sf::Sound& getSound(const std::string&);
	sf::Music& getMusic(const std::string&);
private:
	soundTable sounds_;
	musicTable music_;

	void loadSound(const std::string&, const std::string&);
	void loadMusic(const std::string&, const std::string&);
};
