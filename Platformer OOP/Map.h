#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include "Object.h"

using namespace std;

class Map
{
public:
	vector<vector<int>> grid;
	float cellSize;

	Map(float cellSize = 32.0f);
	void CreateChekerboard(size_t width, size_t height);
	sf::Vector2f CreateFromImage(const sf::Image& image, vector<Object*>& objects);
	void Draw(Renderer& ren);
};

