#include "FrameButton.h"
#include "Application.h"

FrameButton::FrameButton(Application* appPtr, sf::Vector2f size, sf::Vector2f pos, std::string text)
	: appPointer_{ appPtr }, size_ {size}, position_{ pos }, text_{ text } {}

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
	//TODO byt namn
	sf::Text t{ text_,appPointer_->getFont(), 140 };
	window.draw(rect);
	window.draw(t);
}
