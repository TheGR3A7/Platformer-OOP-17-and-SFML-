#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Renderer.h"
#include "Object.h"

using namespace std;

class Map
{
public:
	vector<vector<sf::Texture*>> grid;
	float cellSize;

	Map(float cellSize = 32.0f);
	void CreateChekerboard(size_t width, size_t height);
	sf::Vector2f CreateFromImage(const sf::Image& image, vector<Object*>& objects);
	void Draw(Renderer& ren);
};

