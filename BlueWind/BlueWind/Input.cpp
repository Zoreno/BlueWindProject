#include <SFML\Graphics.hpp>
#include "Input.h"
#include "Application.h"

using namespace std;

Input::Input(Application * appPtr)
	: appPointer_(appPtr)
{
	pressedButtons_.emplace('a', false);
	pressedButtons_.emplace('d', false);
	pressedButtons_.emplace('s', false);
	pressedButtons_.emplace('w', false);
}

bool Input::isPressed(char c) const
{
	return pressedButtons_.find(c)->second;
}

void Input::update()
{
	try
	{
		pressedButtons_.at('w') = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
		pressedButtons_.at('a') = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
		pressedButtons_.at('s') = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
		pressedButtons_.at('d') = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
	}
	catch (const out_of_range& e)
	{
		cerr << e.what() << " @ Input.update()" << endl;
	}
}

void Input::keyPressed(sf::Event event)
{
	appPointer_->getCurrentFrame()->handleKeyEvent(event);
}

void Input::mousePressed(sf::Event event)
{
	appPointer_->getCurrentFrame()->handleMouseEvent(event);
}

