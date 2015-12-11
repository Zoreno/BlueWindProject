#include "UIChatBox.h"

#include <iostream>

using namespace std;

UIChatBox::UIChatBox(UserInterface* uiPtr, Player* playerPtr)
	:UIComponent{ sf::Vector2f(10,450), sf::Vector2f(300,100), uiPtr, playerPtr } 
{}

void UIChatBox::handleKeyEvent(sf::Event ev)
{
}

void UIChatBox::update()
{
	if (inputBuffer_.size() > 4)
	{
		inputBuffer_.pop_back();
	}
}

void UIChatBox::render(GameWindow & window)
{
	sf::RectangleShape frame{ size_ };
	frame.setPosition(position_);
	frame.setFillColor(sf::Color{ 200,200,200,150 });
	frame.setOutlineColor(sf::Color{ 100,100,100,255 });
	frame.setOutlineThickness(4.0f);
	window.draw(frame);

	for (int i{ 0 }; i < (min(4, (int)inputBuffer_.size())); ++i)
	{
		sf::Text conversationText{ inputBuffer_.at(i), ui_->getFont(), 20 };
		conversationText.setPosition(position_ + sf::Vector2f(0, 24.0f*(3-i)));
		conversationText.setColor(sf::Color::Black);
		window.draw(conversationText);
	}
}

void UIChatBox::setConversation(std::string newConversation)
{
	if (newConversation.at(0) == '*')
	{
		inputBuffer_.clear();
		newConversation = newConversation.substr(1, newConversation.length() - 1);
	}
	inputBuffer_.push_front(newConversation);
}
