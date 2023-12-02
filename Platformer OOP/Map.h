#pragma once
#include <vector>
#include "Renderer.h"

using namespace std;

class Map
{
public:
	vector<vector<int>> grid;
	float cellSize;

	Map(float cellSize = 32.0f);
	void CreateChekerboard(size_t width, size_t height);
	void Draw(Renderer& ren);
};

