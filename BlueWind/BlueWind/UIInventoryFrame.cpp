#include "UIInventoryFrame.h"

UIInventoryFrame::UIInventoryFrame(UserInterface * uiPtr, Player * playerPtr)
	:UIComponent{ sf::Vector2f(200,200), sf::Vector2f(400,500), uiPtr, playerPtr , false}
{
	playerInventory_ = playerPtr->getInventory();
}

void UIInventoryFrame::update()
{
}

void UIInventoryFrame::render(GameWindow & window)
{
	sf::RectangleShape frame{ size_ };
	frame.setPosition(position_);
	frame.setFillColor(sf::Color{ 200,200,200,255 });
	frame.setOutlineColor(sf::Color{ 100,100,100,255 });
	frame.setOutlineThickness(4.0f);
	window.draw(frame);
}

void UIInventoryFrame::handleKeyEvent(sf::Event)
{
}
