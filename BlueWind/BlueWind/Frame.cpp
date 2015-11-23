#include "Frame.h"

Frame::Frame(Application * appPtr)
	: appPointer_(appPtr)
{ 
}

Frame::~Frame()
{
	while (!buttons_.empty())
	{
		delete buttons_.back();
		buttons_.pop_back();
	}
}

void Frame::addButton(sf::Vector2f pos, sf::Vector2f size, std::string spriteFile, std::string hoverFile, std::function<void(Application*)> callback)
{
	buttons_.push_back(new FrameButton(appPointer_, pos, size, spriteFile, hoverFile, callback));
}
