#include "Application.h"

using namespace std;

Application::Application()
	: input_{ this }
{
	window_.setFramerateLimit(60);
	currentFrame_ = new Menu(this);
	nextFrame_ = currentFrame_; //
}

void Application::run()
{
	while (window_.isOpen())
	{
		sf::Event event;
		while (window_.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window_.close();

			if (event.type == sf::Event::KeyReleased)
			{
				input_.keyPressed(event);
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
 				input_.mousePressed(event);
			}
		}

		update();

		window_.clear();
		render(window_);
		window_.display();

		if (currentFrame_ != nextFrame_) // Fick skumma fel om frame-bytet gjordes mitt i loopen
			changeCurrentFrame(); //
	}
}

void Application::render(GameWindow & window)
{
	currentFrame_->render(window);
}

void Application::update()
{
	currentFrame_->update();
	input_.update();
}

const Input Application::getInput()
{
	return input_;
}

Frame * Application::getCurrentFrame()
{
	return currentFrame_;
}

void Application::changeCurrentFrame()
{
	delete currentFrame_;
	currentFrame_ = nextFrame_;
	
	/*
	sf::View view = window_.getView();
	view.setCenter(sf::Vector2f(400, 300));
	view.zoom(zoomLevel_);
	window_.setView(view);
	*/
}

const sf::Font& Application::getFont() const
{
	return font_;
}

GameWindow& Application::getGameWindow()
{
	return window_;
}

SoundHandler & Application::getSoundHandler()
{
	return soundHandler_;
}

void Application::setNextFrame(Frame* framePtr)
{
	nextFrame_ = framePtr;
}

void Application::setZoomLevel(float zoom)
{
	zoomLevel_ = zoom;
}
