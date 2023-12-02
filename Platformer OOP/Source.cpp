#include <SFML/Graphics.hpp>

#include "Character.h"
#include "Game.h"
#include "Camera.h"
#include "Renderer.h"
#include "Standard Values.h"

using namespace std;

int main()
{
	sf::RenderWindow win(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Platformer");
	sf::Clock deltaClock;
	Camera camera;
	Renderer ren(win);

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

		win.setView(camera.GetView(win.getSize()));
		Update(deltaTime);


		win.clear(sf::Color(0, 219, 255));
		Render(ren);
		win.display();
	}
}