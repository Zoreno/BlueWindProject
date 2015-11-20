#include "UIBar.h"
#include <string>

using namespace std;

UIBar::UIBar(sf::Vector2f position, sf::Vector2f size, sf::Color color, std::string postfix, UserInterface* uiPtr)
	:fillLevel_{ 1 }, position_ {position}, size_ {size}, color_{color}, postfix_ {postfix}, ui_{uiPtr}
{
}

void UIBar::update(float current, float max)
{
	text_ = to_string(static_cast<int>(current)) + '/' + to_string(static_cast<int>(max));
	if (max != 0 && current > 0)
	{
		fillLevel_ = current / max;
		return;
	}
	fillLevel_ = 0;
}

void UIBar::render(GameWindow & window)
{
	sf::RectangleShape border{ size_ };
	border.setOutlineColor(sf::Color::Black);
	border.setFillColor(sf::Color::White);
	border.setOutlineThickness(2.0f);

	sf::RectangleShape fill{ sf::Vector2f(size_.x * fillLevel_, size_.y) };
	fill.setOutlineColor(sf::Color::Transparent);
	fill.setFillColor(color_);

	border.setPosition(position_);
	fill.setPosition(position_);

	window.draw(border);
	window.draw(fill);

	sf::Text text{ text_ + postfix_, ui_->getFont(), 16 };
	text.setPosition(position_ + sf::Vector2f(2, 0));
	text.setColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);
	window.draw(text);
}
