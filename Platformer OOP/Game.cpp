#include "Game.h"
#include "Resources.h"
#include "Map.h"
#include "Character.h"
#include "Physics.h"
#include <SFML/Audio.hpp>
#include <filesystem>

Map gameMap(1.0f);
Camera camera(20.0f);
Character player;

sf::Music music;

void Begin(const sf::Window& win)
{
	for (auto& file : filesystem::directory_iterator("./Images/"))
	{
		if (file.is_regular_file() && (file.path().extension() == ".png" || file.path().extension() == ".jpg"))
		{
			Resources::textures[file.path().filename().string()].loadFromFile(file.path().string());
		}
	}

	for (auto& file : filesystem::directory_iterator("./Sounds/"))
	{
		if (file.is_regular_file() && (file.path().extension() == ".ogg" || file.path().extension() == ".wav"))
		{
			Resources::sounds[file.path().filename().string()].loadFromFile(file.path().string());
		}
	}

	music.openFromFile("Sounds/mainMusic.wav");
	music.setLoop(true);
	music.setVolume(30);

	Physics::Init();

	sf::Image image;
	image.loadFromFile("Images/map.png");
	player.position = gameMap.CreateFromImage(image);
	player.Begin();

	music.play();
}

void Update(float deltaTime)
{
	Physics::Update(deltaTime);
	player.Update(deltaTime);
	camera.position = player.position;
}

void Render(Renderer& ren)
{
	ren.Draw(Resources::textures["background.png"], camera.position, camera.GetViewSize());

	gameMap.Draw(ren);
	player.Draw(ren);

	Physics::DebugDraw(ren);
}