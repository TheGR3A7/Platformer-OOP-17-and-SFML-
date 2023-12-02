#include "Map.h"


void Map::CreateChekerboard(size_t width, size_t height)
{
	grid = vector(width, vector(height, 0));

	int last = 0;

	for (auto& column : grid)
	{
		for (auto& cell : column)
		{
			cell = !last;
			last = cell;
		}
	}
}