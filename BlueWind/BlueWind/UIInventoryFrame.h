#pragma once

#include "UIComponent.h"
#include "UserInterface.h"

class UIInventoryFrame : public UIComponent
{
public:
	UIInventoryFrame(UserInterface*, Player*);
	UIInventoryFrame() = delete;
	UIInventoryFrame(const UIInventoryFrame&) = delete;
	UIInventoryFrame& operator=(const UIInventoryFrame&) = delete;

	void update();
	void render(GameWindow&);
	void handleKeyEvent(sf::Event);

private:
	Inventory* playerInventory_;
	unsigned int inventorySize_;
};