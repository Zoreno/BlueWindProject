#pragma once

#include <SFML\Graphics.hpp>
#include "GameWindow.h"
#include "Player.h"

class UserInterface;

class UIComponent
{
public:
	UIComponent(sf::Vector2f, sf::Vector2f, UserInterface*, Player*, bool = true);
	UIComponent() = delete;
	UIComponent(const UIComponent&) = delete;
	UIComponent& operator=(const UIComponent&) = delete;

	virtual void handleKeyEvent(sf::Event) = 0;

	virtual void update() = 0;
	virtual void render(GameWindow&) = 0;

	bool isVisible() const;
	sf::Vector2f getPosition() const;
	void toggleVisible();
	void setVisible(bool);
protected:
	sf::Vector2f position_;
	sf::Vector2f size_;
	UserInterface* ui_;
	Player* player_;
	bool visible_;
};