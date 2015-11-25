#include "UIPortrait.h"
#include <string>

using namespace std;

UIPortrait::UIPortrait(UserInterface * uiPtr, Player * playerPtr)
	:UIComponent{ sf::Vector2f(10,10), sf::Vector2f(100,120), uiPtr, playerPtr },
	healthBar_{position_ + sf::Vector2f(10,40), sf::Vector2f(80,20), sf::Color::Red, "HP", uiPtr},
	manaBar_{ position_ + sf::Vector2f(10,60), sf::Vector2f(80,20), sf::Color{0,100,255,255}, "MP", uiPtr },
	expBar_{ position_ + sf::Vector2f(10,80), sf::Vector2f(80,20), sf::Color::Green, "XP", uiPtr }
{
}

void UIPortrait::handleKeyEvent(sf::Event)
{
}

void UIPortrait::update()
{
	healthBar_.update(player_->getHealth(), player_->getMaxHealth());
	manaBar_.update(player_->getMana(), player_->getMaxMana());
	expBar_.update(player_->getExperience(), player_->getMaxExperience());
}

void UIPortrait::render(GameWindow & window)
{
	sf::RectangleShape frame{ size_ };
	frame.setPosition(position_);
	frame.setFillColor(sf::Color{ 200,200,200,255 });
	frame.setOutlineColor(sf::Color{ 100,100,100,255 });
	frame.setOutlineThickness(4.0f);
	window.draw(frame);

	sf::Text nameText{ player_->getName() + "  " + to_string(player_->getLevel()), ui_->getFont(), 30 };
	nameText.setPosition(position_);
	nameText.setColor(sf::Color::Black);
	window.draw(nameText);

	healthBar_.render(window);
	manaBar_.render(window);
	expBar_.render(window);

}
