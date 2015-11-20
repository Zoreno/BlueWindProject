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

void Frame::addButton(sf::Vector2f pos, std::string file, sf::Vector2f size)
{
	buttons_.push_back(new FrameButton(appPointer_, pos, file, size));
}
