#pragma once
#include <vector>

using namespace std;

class Map
{
public:
	vector<vector<int>> grid;

	void CreateChekerboard(size_t width, size_t height);
};

