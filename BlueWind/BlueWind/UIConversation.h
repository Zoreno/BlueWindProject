#pragma once

#include "UIComponent.h"
#include "UserInterface.h"

class UIConversation : public UIComponent
{
public:
	UIConversation(UserInterface*, Player*);
	UIConversation() = delete;
	UIConversation(const UIConversation&) = delete;
	UIConversation& operator=(const UIConversation&) = delete;

	void update() override;
	void render(GameWindow&) override;

	void setConversation(std::string);

private:
	std::string conversation_{ "Test test test test test test test test" };
};