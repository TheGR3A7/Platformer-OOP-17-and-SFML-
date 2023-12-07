#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Renderer.h"
#include "Standard Values.h"

using namespace std;

int main()
{
	sf::RenderWindow win(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Platformer");
	sf::Clock deltaClock;
	Renderer ren(win);

	win.setFramerateLimit(60);
	Begin(win);

	while (win.isOpen())
	{
		float deltaTime = deltaClock.restart().asSeconds();

		sf::Event event;

		while (win.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				win.close();
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{

				}

			}

		}

		Update(deltaTime);
		win.clear(sf::Color(0, 219, 255));

		win.setView(camera.GetView(win.getSize()));
		Render(ren);

		win.setView(camera.GetUIView());
		RenderUI(ren);

		win.display();
	}
}