#include "Application.h"

using namespace std;

Application::Application()
{
	if (!font_.loadFromFile("res/calibri.ttf"))
	{
		//TODO lägg till exception
		cout << "Kan inte läsa font" << endl;
	}
	currentFrame_ = new Game(this);
}

void Application::run()
{
	cout << "Program running..." << endl;

	window_.setFramerateLimit(60);

	while (window_.isOpen())
	{
		sf::Event event;
		while (window_.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window_.close();
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
}

const sf::Font& Application::getFont() const
{
	return font_;
}
