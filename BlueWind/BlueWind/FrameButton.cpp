#include "FrameButton.h"
#include "Application.h"

using namespace std;

FrameButton::FrameButton(Application* appPtr, sf::Vector2f pos, std::string file, sf::Vector2f size)
	: appPointer_{ appPtr }, position_{ pos }, file_{ file }, size_{ size } 
{
	// TODO Fixa callback!
}

sf::Vector2f FrameButton::getPosition() const
{
	return position_;
}

sf::Vector2f FrameButton::getSize() const
{
	return size_;
}

void FrameButton::update()
{
	
}

void FrameButton::render(GameWindow & window)
{
	sf::Texture bTexture;

	if (!bTexture.loadFromFile(file_))
		cout << "Could not load" << file_ << endl;

	sprite_.setTexture(bTexture);
	sprite_.setPosition(position_);
	window.draw(sprite_);
}

void FrameButton::callback()
{

}
