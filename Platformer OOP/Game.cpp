#include "Game.h"
#include "Resources.h"
#include "Map.h"
#include "Character.h"
#include "Physics.h"
#include <filesystem>

Map gameMap(1.0f);
Camera camera(20.0f);
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

	Physics::Init();

	sf::Image image;
	image.loadFromFile("Images/map.png");
	player.position = gameMap.CreateFromImage(image);
	player.Begin();
}

void Update(float deltaTime)
{
	Physics::Update(deltaTime);
	player.Update(deltaTime);
	camera.position = player.position;
}

void Render(Renderer& ren)
{
	gameMap.Draw(ren);
	player.Draw(ren);
}