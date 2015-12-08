#pragma once

#include <map>
#include <string>
#include <SFML\Graphics.hpp>
#include <stdexcept>

using textureTable = std::map<const std::string, sf::Texture*>;

class TextureException : public std::logic_error
{
public:
	using std::logic_error::logic_error;
};

class TextureHandler
{
public:
	TextureHandler();
	TextureHandler(const TextureHandler&) = delete;
	TextureHandler& operator=(const TextureHandler&) = delete;

	~TextureHandler();

	sf::Texture& getTextureRef(const std::string&);
private:
	textureTable textures_;

	void loadTexture(const std::string&, const std::string&);
};