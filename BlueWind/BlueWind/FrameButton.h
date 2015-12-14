/* IDENTIFIERING
*
* Filnamn:    FrameButton.h
* Enhetsnamn: FrameButton
* Typ:        Moduldeklaration
* Revision:   1
* Skriven av: Simon Arkeholt, Fredrik Gustafsson
*
*
* BESKRIVNING
*
* Denna modul representerar en NPC i spelet.
*
* REVISIONSBERÄTTELSE
*
* Revision     Datum   Förändringar
*
* 1            151214  Ursprungsversion
*
*/

#pragma once

#include <SFML\Graphics.hpp>
#include <string>
#include "GameWindow.h"
#include <functional>
#include <stdexcept>

class Application;

class FrameButtonException : public std::logic_error
{
public:
	using std::logic_error::logic_error;
};

class FrameButton
{
public:
	FrameButton(Application*,sf::Vector2f, sf::Vector2f, std::string, std::string, std::function<void (Application*)>);
	FrameButton(const FrameButton&) = delete;
	FrameButton& operator=(const FrameButton&) = delete;

	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;

	void update();
	void render(GameWindow&);
	void clicked();
	bool mouseOnButton(sf::Vector2i);

private:
	Application* appPointer_;
	sf::Vector2f position_;
	sf::Vector2f size_;
	sf::Texture normalTexture;
	sf::Texture hoverTexture;
	sf::Sprite sprite_;
	std::function<void(Application*)> callback_;
};