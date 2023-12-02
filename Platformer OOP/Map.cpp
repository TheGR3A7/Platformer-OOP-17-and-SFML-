#include "Map.h"
#include "Resources.h"

Map::Map(float cellSize) : cellSize(cellSize), grid()
{
}


void Map::CreateChekerboard(size_t width, size_t height)
{
	grid = vector(width, vector(height, 1));

	int last = 0;

	for (auto& column : grid)
	{
		for (auto& cell : column)
		{
			last = cell = !last;
		}
		if (width % 2 == 0)
			last = !last;
	}
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
				ren.Draw(Resources::textures["brick2.png"], sf::Vector2f(cellSize * x + cellSize / 2.0f, cellSize * y + cellSize / 2.0f), sf::Vector2f(cellSize, cellSize));
			}
			y++;
		}
		x++;
	}
}