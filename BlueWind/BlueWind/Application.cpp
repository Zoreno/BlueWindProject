#include "Application.h"

using namespace std;

Application::Application()
	: input_{ this }
{
	currentFrame_ = new Menu(this);
}

void Application::run()
{
	cout << "Program running..." << endl;

	window_.setFramerateLimit(60);
	sf::View view = window_.getView();
	window_.setView(view);

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

void Application::startNewGame()
{
	// TODO Fixa mer allmän "changeframe"-funktion
	soundHandler_.stopMusic("menuMusic");
	
	delete currentFrame_;
	currentFrame_ = new Game(this);
	
	sf::View view = window_.getView();
	view.zoom(0.4f);
	window_.setView(view);
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
