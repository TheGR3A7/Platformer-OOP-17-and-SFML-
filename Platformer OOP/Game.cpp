#include "Game.h"
#include "Resources.h"
#include "Map.h"
#include <filesystem>

Map gameMap;
Camera camera(320.0f);

void Begin(const sf::Window& win)
{
	for (auto& file : filesystem::directory_iterator("./Images/"))
	{
		if (file.is_regular_file() && (file.path().extension() == ".png" || file.path().extension() == ".jpg"))
		{
			Resources::textures[file.path().filename().string()].loadFromFile(file.path().string());
		}
	}

	gameMap.CreateChekerboard(10, 10);
	camera.position = sf::Vector2f(160.0f, 160.0f);
}

void Update(float deltaTime)
{

}

void Render(Renderer& ren)
{
	gameMap.Draw(ren);
}