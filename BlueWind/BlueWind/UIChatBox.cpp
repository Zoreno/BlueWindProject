#include "UIChatBox.h"

#include <iostream>

using namespace std;

UIChatBox::UIChatBox(UserInterface* uiPtr, Player* playerPtr)
	:UIComponent{ sf::Vector2f(10,450), sf::Vector2f(300,100), uiPtr, playerPtr } 
{
	inputBuffer_.push_back("Hej.");
	inputBuffer_.push_back("Detta är en sträng.");
	inputBuffer_.push_back("Detta är också en sträng.");
}

void UIChatBox::handleKeyEvent(sf::Event ev)
{

	switch(ev.key.code)
	{
	case sf::Keyboard::E:
		if (!inputBuffer_.empty())
		{
			//inputBuffer_.pop_front();
		}
		break;
	default:
		break;
	}
}

void UIChatBox::update()
{

}

void UIChatBox::render(GameWindow & window)
{
	sf::RectangleShape frame{ size_ };
	frame.setPosition(position_);
	frame.setFillColor(sf::Color{ 200,200,200,100 });
	frame.setOutlineColor(sf::Color{ 100,100,100,255 });
	frame.setOutlineThickness(4.0f);
	window.draw(frame);


	for (int i{ 0 }; i < (min(4, (int)inputBuffer_.size())); ++i)
	{
		sf::Text conversationText{ inputBuffer_.at(i), ui_->getFont(), 20 };
		conversationText.setPosition(position_ + sf::Vector2f(0, 24*(3-i)));
		conversationText.setColor(sf::Color::Black);
		window.draw(conversationText);
	}
}

void UIChatBox::setConversation(std::string newConversation)
{
	inputBuffer_.push_front(newConversation);
}
