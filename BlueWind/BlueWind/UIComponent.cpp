#include "UIComponent.h"

bool UIComponent::isVisible() const
{
	return visible_;
}

sf::Vector2f UIComponent::getPosition() const
{
	return position_;
}

void UIComponent::toggleVisible()
{
	visible_ = !visible_;
}

void UIComponent::setVisible(bool value)
{
	visible_ = value;
}
