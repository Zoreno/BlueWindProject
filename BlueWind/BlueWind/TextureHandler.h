/* IDENTIFIERING
*
* Filnamn:    TextureHandler.h
* Enhetsnamn: TextureHandler
* Typ:        Moduldeklaration
* Revision:   1
* Skriven av: Simon Arkeholt, Fredrik Gustafsson
*
*
* BESKRIVNING
*
* Denna modul representerar texturhanteraren i spelet.
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151214  Ursprungsversion
*
*/

#pragma once

/*
* REFERERADE BIBLIOTEK OCH MODULER
*/

#include <map>
#include <string>
#include <SFML\Graphics.hpp>
#include <stdexcept>

using textureTable = std::map<const std::string, sf::Texture*>;

/*
* KLASS TextureException
*
* BASKLASSER
*
* logic_error
*
* BESKRIVNING
*
* Klassen kastar undantag för TextureHandler.
*
* KONSTRUKTORER
*
* default-konstruktor.
*
* DATAMEDLEMMAR
*
* -
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151214  Ursprungsversion
*
*/

class TextureException : public std::logic_error
{
public:
	using std::logic_error::logic_error;
};

/*
* KLASS TextureHandler
*
* BASKLASSER
*
* -
*
* BESKRIVNING
*
* Klassen representerar texturhateraren i spelet. TextureHandler läser in, sparar och ger åtkomst till alla texturer som används i spelet. 
*
* KONSTRUKTORER
*
* TextureHandler()
*
* DATAMEDLEMMAR
*
* textures_:		TextureTable med alla texturer lagrade.
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151214  Ursprungsversion
*
*/

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
};// class TextureHandler

/*
* SLUT PÅ FILEN TextureHandler.h
*/