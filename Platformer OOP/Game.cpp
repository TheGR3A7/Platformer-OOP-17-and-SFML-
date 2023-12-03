#include "Game.h"
#include "Resources.h"
#include "Map.h"
#include <filesystem>

Map gameMap(16.0f);
Camera camera(320.0f);

const float movementSpeed = 180.0f;

void Begin(const sf::Window& win)
{
	for (auto& file : filesystem::directory_iterator("./Images/"))
	{
		if (file.is_regular_file() && (file.path().extension() == ".png" || file.path().extension() == ".jpg"))
		{
			Resources::textures[file.path().filename().string()].loadFromFile(file.path().string());
		}
	}

	sf::Image image;
	image.loadFromFile("Images/map.png");
	gameMap.CreateFromImage(image);
	
	camera.position = sf::Vector2f(160.0f, 160.0f);
}

void Update(float deltaTime)
{
	float move = movementSpeed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		move *= 2;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		camera.position.x += move * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		camera.position.x -= move * deltaTime;
}

void Render(Renderer& ren)
{
	gameMap.Draw(ren);
}