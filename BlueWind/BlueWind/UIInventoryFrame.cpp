#include "UIInventoryFrame.h"
#include <algorithm>
#include <string>

using namespace std;

UIInventoryFrame::UIInventoryFrame(UserInterface * uiPtr, Player * playerPtr)
	:UIComponent{ sf::Vector2f(480,50), sf::Vector2f(300,500), uiPtr, playerPtr , false}
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

	sf::Text conversationText{ "Inventory", ui_->getFont(), 40 };
	conversationText.setPosition(position_ + sf::Vector2f(10, 16 ));
	conversationText.setColor(sf::Color::Black);
	window.draw(conversationText);

	for (int i{ 0 }; i <  (min(8, playerInventory_->getSize())); ++i)
	{
		Item* item = playerInventory_->at(i);
		item->render(window, position_ + sf::Vector2f(10, 80 + 52 * i));

		/*
		sf::RectangleShape item{ sf::Vector2f(48,48) };
		item.setPosition(position_ + sf::Vector2f(10, 80 + 52 * i));
		item.setFillColor(sf::Color::Red);
		window.draw(item);
		*/

		sf::Text conversationText{ item->getName(), ui_->getFont(), 30 };
		conversationText.setPosition(position_ + sf::Vector2f(80, 82 + 52 * i));
		conversationText.setColor(sf::Color::Black);
		window.draw(conversationText);

	}
}

void UIInventoryFrame::handleKeyEvent(sf::Event ev)
{
	switch (ev.key.code)
	{
	case sf::Keyboard::T:
		toggleVisible();
		break;
	}
}
