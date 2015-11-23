#include "UIConversation.h"

UIConversation::UIConversation(UserInterface* uiPtr, Player* playerPtr)
	:UIComponent{ sf::Vector2f(690,470), sf::Vector2f(100,120), uiPtr, playerPtr } 
{}

void UIConversation::update()
{

}

void UIConversation::render(GameWindow & window)
{
	sf::RectangleShape frame{ size_ };
	frame.setPosition(position_);
	frame.setFillColor(sf::Color{ 200,200,200,255 });
	frame.setOutlineColor(sf::Color{ 100,100,100,255 });
	frame.setOutlineThickness(4.0f);
	window.draw(frame);

	sf::Text conversationText{ conversation_, ui_->getFont(), 20 };
	conversationText.setPosition(position_);
	conversationText.setColor(sf::Color::Black);
	window.draw(conversationText);
}

void UIConversation::setConversation(std::string newConversation)
{
	conversation_ = newConversation;
}
