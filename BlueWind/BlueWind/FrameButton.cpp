#include "FrameButton.h"

FrameButton::FrameButton(sf::Vector2f size, sf::Vector2f pos, std::string text)
	: size_{size}, position_{pos}, text_{text} {}

sf::Vector2f FrameButton::getPosition() const
{
	return position_;
}

void FrameButton::update()
{}

void FrameButton::render(GameWindow & window)
{
	sf::RectangleShape rect{ size_ };
	rect.move(position_);
	rect.setFillColor(sf::Color::Magenta);
	//TODO lägg till font
	//sf::Text t{text_,}
	window.draw(rect);
}
