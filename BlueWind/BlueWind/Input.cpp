#include "Input.h"

#include <SFML\Graphics.hpp>

Input::Input()
{
	pressedButtons_.emplace('a', false);
	pressedButtons_.emplace('d', false);
	pressedButtons_.emplace('s', false);
	pressedButtons_.emplace('w', false);
	pressedButtons_.emplace(' ', false);
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		pressedButtons_[' '] = true;
	else
		pressedButtons_[' '] = false;
}
