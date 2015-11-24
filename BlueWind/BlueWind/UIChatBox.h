#pragma once

#include "UIComponent.h"
#include "UserInterface.h"
#include <deque>

class UIChatBox : public UIComponent
{
public:
	UIChatBox(UserInterface*, Player*);
	UIChatBox() = delete;
	UIChatBox(const UIChatBox&) = delete;
	UIChatBox& operator=(const UIChatBox&) = delete;

	void handleKeyEvent(sf::Event) override;

	void update() override;
	void render(GameWindow&) override;

	void setConversation(std::string);

private:
	std::deque<std::string> inputBuffer_;
};