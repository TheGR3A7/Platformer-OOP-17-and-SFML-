#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Renderer.h"

using namespace std;

class Map
{
public:
	vector<vector<int>> grid;
	float cellSize;

	Map(float cellSize = 32.0f);
	void CreateChekerboard(size_t width, size_t height);
	void CreateFromImage(const sf::Image& image);
	void Draw(Renderer& ren);
};

