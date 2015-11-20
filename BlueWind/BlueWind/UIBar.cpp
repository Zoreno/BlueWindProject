#include "UIBar.h"

void UIBar::update(int current, int max)
{
	if (max != 0)
	{
		fillLevel_ = current / max;
		return;
	}
	fillLevel_ = 1;
}

void UIBar::render(GameWindow & window)
{
	sf::RectangleShape border{ size_ };
	border.setOutlineColor(sf::Color::Black);
	border.setFillColor(sf::Color::Transparent);

	sf::RectangleShape fill{ sf::Vector2f(size_.x * fillLevel_, size_.y) };
	fill.setOutlineColor(sf::Color::Transparent);
	fill.setFillColor(color_);

	border.setPosition(position_);
	fill.setPosition(position_);

	window.draw(border);
	window.draw(fill);
}
