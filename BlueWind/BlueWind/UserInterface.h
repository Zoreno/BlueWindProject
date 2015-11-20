#pragma once

#include <vector>
#include "UIComponent.h"
#include "GameWindow.h"

class UserInterface
{
public:
	UserInterface() = delete;
	UserInterface(const UserInterface&) = delete;
	UserInterface& operator=(const UserInterface&) = delete;

	void update();
	void render(GameWindow&);
private:
	std::vector<UIComponent*> components_;
	void loadComponents();
};