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

void Frame::addButton(sf::Vector2f size, sf::Vector2f pos, std::string text)
{
	buttons_.push_back(new FrameButton(size, pos, text));
}
