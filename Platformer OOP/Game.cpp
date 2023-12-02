#include "Game.h"
#include "Resources.h"
#include <filesystem>


void Begin(const sf::Window& win)
{
	for (auto& file : filesystem::directory_iterator("./Images/"))
	{
		if (file.is_regular_file() && (file.path().extension() == ".png" || file.path().extension() == ".jpg"))
		{
			Resources::textures[file.path().filename().string()].loadFromFile(file.path().string());
		}
	}
}

void Update(float deltaTime)
{

}

void Render(Renderer& ren)
{
	ren.Draw(Resources::textures["brick2.png"], sf::Vector2f(), sf::Vector2f(4.75f, 4.75f));
}