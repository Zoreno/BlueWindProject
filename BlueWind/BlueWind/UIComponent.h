#pragma once

#include <SFML\Graphics.hpp>
#include "GameWindow.h"
#include "Player.h"

class UIComponent
{
public:
	UIComponent() = delete;
	UIComponent(const UIComponent&) = delete;
	UIComponent& operator=(const UIComponent&) = delete;

	virtual void update() = 0;
	virtual void render(GameWindow&) = 0;

	bool isVisible() const;
	sf::Vector2f getPosition() const;
	void toggleVisible();
	void setVisible(bool);
protected:
	bool visible_{ true };
	sf::Vector2f position_;
	Player* player_;
};