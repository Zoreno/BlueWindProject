#include "Frame.h"

Frame::Frame(Application * appPtr)
	: appPointer_(appPtr)
{ 
}

void Frame::addButton(FrameButton button)
{
	buttons_.push_back(button);
}
