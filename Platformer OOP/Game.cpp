#include "Game.h"
#include "Resources.h"
#include "Map.h"
#include "Character.h"
#include <filesystem>

Map gameMap(16.0f);
Camera camera(320.0f);
Character player;


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
	player.position = gameMap.CreateFromImage(image);
	
}

void Update(float deltaTime)
{
	player.Update(deltaTime);
	camera.position = player.position;
}

void Render(Renderer& ren)
{
	gameMap.Draw(ren);
	player.Draw(ren);
}