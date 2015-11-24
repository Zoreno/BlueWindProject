#include "UIComponent.h"

UIComponent::UIComponent(sf::Vector2f position, sf::Vector2f size, UserInterface * uiPtr, Player * playerPtr, bool visible)
	:position_{position}, 
	size_{size}, 
	ui_{uiPtr}, 
	player_{playerPtr}, 
	visible_{visible}
{
}

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
