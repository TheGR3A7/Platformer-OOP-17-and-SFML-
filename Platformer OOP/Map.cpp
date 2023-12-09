#include "Map.h"
#include "Resources.h"
#include "Physics.h"
#include "Object.h"
#include "Coin.h"
#include "Enemy.h"
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>

using namespace std;

Map::Map(float cellSize) : cellSize(cellSize), grid()
{
}


void Map::CreateChekerboard(size_t width, size_t height)
{
	grid = vector(width, vector(height, (sf::Texture*)nullptr));

	bool last = 0;

	for (auto& column : grid)
	{
		for (auto& cell : column)
		{
			last = !last;
			if (last)
				cell = &Resources::textures["brick.png"];
		}
		if (width % 2 == 0)
			last = !last;
	}
}

sf::Vector2f Map::CreateFromImage(const sf::Image& image, vector<Object*> &objects)
{
	grid.clear();
	grid = vector(image.getSize().x, vector(image.getSize().y,(sf::Texture*)nullptr));

	sf::Vector2f characterPosition;

	for (size_t x = 0; x < grid.size(); x++)
	{
		for (size_t y = 0; y < grid[x].size(); y++) 
		{
			sf::Color color = image.getPixel(x, y);
			Object* object = nullptr;

			if (color == sf::Color::Red)
			{
				characterPosition = sf::Vector2f(cellSize * x + cellSize / 2.0f, cellSize * y + cellSize / 2.0f);
				continue;
			}
			else if (color == sf::Color::Black)
			{
				grid[x][y] = &Resources::textures["brick.png"];
			}
			else if (color == sf::Color::Blue)
			{
				grid[x][y] = &Resources::textures["marble.png"];
			}
			else if (color == sf::Color::Yellow)
			{
				object = new Coin();
			}
			else if (color == sf::Color::Green)
			{
				object = new Enemy();
			}

			if (object)
			{
				object->position = sf::Vector2f(cellSize * x + cellSize / 2.0f, cellSize * y + cellSize / 2.0f);
				objects.push_back(object);
			}
			else if (grid[x][y])
			{
				b2BodyDef bodyDef;
				bodyDef.position.Set(cellSize * x + cellSize / 2.0f, cellSize * y + cellSize / 2.0f);
				b2Body* body = Physics::world.CreateBody(&bodyDef);
				b2PolygonShape shape;
				shape.SetAsBox(cellSize / 2.0f, cellSize / 2.0f);

				FixtureData* fixtureData = new FixtureData();
				fixtureData->type = FixtureDataType::MapTile;
				fixtureData->mapX = x;
				fixtureData->mapY = y;

				b2FixtureDef fixtureDef;
				fixtureDef.userData.pointer = (uintptr_t)fixtureData; //приведение указателя к беззнаковому целочисленному типу для сохранения указателя на объект 
				fixtureDef.density = 0.0f;
				fixtureDef.shape = &shape;
				body->CreateFixture(&fixtureDef);
			}
		}
	}

	return characterPosition;
}

void Map::Draw(Renderer& ren)
{
	int x = 0;
	for (const auto& column : grid)
	{
		int y = 0;
		for (const auto& cell : column)
		{
			if (cell)
			{
				ren.Draw(*cell, sf::Vector2f(cellSize * x + cellSize / 2.0f, cellSize * y + cellSize / 2.0f), sf::Vector2f(cellSize, cellSize));
			}
			y++;
		}
		x++;
	}
}