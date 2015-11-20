#include "Input.h"
#include "Application.h"

#include <SFML\Graphics.hpp>


Input::Input(Application * appPtr)
	: appPointer_(appPtr)
{
	pressedButtons_.emplace('a', false);
	pressedButtons_.emplace('d', false);
	pressedButtons_.emplace('s', false);
	pressedButtons_.emplace('w', false);
}

void Input::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		pressedButtons_['w'] = true;
	else
		pressedButtons_['w'] = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		pressedButtons_['a'] = true;
	else
		pressedButtons_['a'] = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		pressedButtons_['s'] = true;
	else
		pressedButtons_['s'] = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		pressedButtons_['d'] = true;
	else
		pressedButtons_['d'] = false;
}

void Input::keyPressed(sf::Event event)
{
	if ((event.key.code == sf::Keyboard::Space) || (event.key.code == sf::Keyboard::I))
		appPointer_->getCurrentFrame()->handleKeyEvent(event);
}


