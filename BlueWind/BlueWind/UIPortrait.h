#pragma once

#include "UIComponent.h"
#include "UIBar.h"
#include "UserInterface.h"

class UIPortrait : public UIComponent
{
public:
	UIPortrait(UserInterface*, Player*);
	UIPortrait() = delete;
	UIPortrait(const UIPortrait&) = delete;
	UIPortrait& operator=(const UIPortrait&) = delete;

	void update() override;
	void render(GameWindow&) override;

private:
	UIBar healthBar_;
	UIBar manaBar_;
	UIBar expBar_;
};