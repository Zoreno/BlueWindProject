#pragma once

#include <map>
#include <string>
#include <SFML/Audio.hpp>
#include <stdexcept>

using soundTable = std::map<const std::string, sf::SoundBuffer*>;
using musicTable = std::map<const std::string, sf::Music*>;

class SoundException : public std::logic_error
{
public:
	using std::logic_error::logic_error;
};

class SoundHandler
{
public:
	SoundHandler();
	SoundHandler(const SoundHandler&) = delete;
	SoundHandler& operator=(const SoundHandler&) = delete;

	~SoundHandler();

	void playSound(const std::string&);
	void playMusic(const std::string&);
	void stopMusic();
	
private:
	soundTable sounds_;
	musicTable music_;
	sf::Sound currentSound_;
	std::string currentMusic_;

	void loadSound(const std::string&, const std::string&);
	void loadMusic(const std::string&, const std::string&);
};
