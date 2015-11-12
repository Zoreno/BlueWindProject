#include "Application.h"

using namespace std;

Application::Application()
{
}

void Application::run()
{
	cout << "Program running..." << endl;

	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		update();

		window.clear();
		render(window);
		window.display();
	}
}

void Application::render(GameWindow & window)
{
}

void Application::update()
{

}
