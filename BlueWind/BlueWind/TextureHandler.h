#pragma once

#include <map>
#include <string>
#include <SFML\Graphics.hpp>

using textureTable = std::map<const std::string, sf::Texture*>;

class TextureHandler
{
public:
	TextureHandler();
	TextureHandler(const TextureHandler&) = delete;
	TextureHandler& operator=(const TextureHandler&) = delete;

	//TODO destruktor

	sf::Texture& getTextureRef(const std::string&);
private:
	textureTable textures_;

	void loadTexture(const std::string&, const std::string&);
};