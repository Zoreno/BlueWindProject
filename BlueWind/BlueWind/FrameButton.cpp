#include "FrameButton.h"
#include "Application.h"

using namespace std;

FrameButton::FrameButton(Application* appPtr, sf::Vector2f pos, sf::Vector2f size, std::string normalFile, std::string hoverFile, std::function<void(Application*)> callbackFunc)
	: appPointer_{ appPtr }, position_{ pos }, size_{ size }, callback_{callbackFunc}
{
	if (!normalTexture.loadFromFile(normalFile))
		cout << "Could not load" << normalFile << endl;
	if (!hoverTexture.loadFromFile(hoverFile))
		cout << "Could not load" << hoverFile << endl;
}

sf::Vector2f FrameButton::getPosition() const
{
	return position_;
}

sf::Vector2f FrameButton::getSize() const
{
	return size_;
}

void FrameButton::update()
{
	sf::Vector2i mousePosition{ sf::Mouse::getPosition(appPointer_->getGameWindow()) };
		
	if (mouseOnButton(mousePosition))
	{
		sprite_.setTexture(hoverTexture);
		// appPointer_->getSoundHandler().playSound("menuClick"); // TODO Fixa!
	}
	else
		sprite_.setTexture(normalTexture);	
}

void FrameButton::render(GameWindow & window)
{
	sprite_.setPosition(position_);
	window.draw(sprite_);
}

void FrameButton::clicked()
{
	appPointer_->getSoundHandler().playSound("menuClick");
	callback_(appPointer_);
}

bool FrameButton::mouseOnButton(sf::Vector2i mousePosition)
{
	return (mousePosition.x > position_.x && mousePosition.x < position_.x + size_.x &&
			mousePosition.y > position_.y && mousePosition.y < position_.y + size_.y);
}


