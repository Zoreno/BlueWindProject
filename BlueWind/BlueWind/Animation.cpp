#include "Animation.h"
#include "Entity.h"

void Animation::render(GameWindow& window)
{
	currentSprite_.setPosition(entityPtr_->getPosition());
	window.draw(currentSprite_);
}
