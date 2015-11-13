#pragma once

#include <map>
#include <string>
#include <SFML\Graphics.hpp>

using table = std::map<const std::string, sf::Texture>;

class TextureHandler
{
public:
	TextureHandler();

	sf::Texture& getTextureRef(const std::string&);
private:
	 table textures_;

	void loadTexture(const std::string&, const std::string&);
};