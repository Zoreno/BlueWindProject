#include "FrameButton.h"
#include "Application.h"

using namespace std;

FrameButton::FrameButton(Application* appPtr, sf::Vector2f pos, string file)
	: appPointer_{ appPtr }, position_{ pos }, file_{ file } {}

sf::Vector2f FrameButton::getPosition() const
{
	return position_;
}

void FrameButton::update()
{}

void FrameButton::render(GameWindow & window)
{
	sf::Texture bTexture;

	if (!bTexture.loadFromFile(file_))
		cout << "Could not load menu" << endl;

	sprite_.setTexture(bTexture);
	sprite_.setPosition(position_);
	window.draw(sprite_);
}
