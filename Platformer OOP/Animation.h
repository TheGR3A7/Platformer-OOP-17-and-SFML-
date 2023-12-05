#pragma once
#include <SFML/Graphics.hpp>

using namespace std;

struct AnimFrame
{
	AnimFrame(float time = 0.0f, sf::Texture texture = sf::Texture()) : time(time), texture(texture)
	{
	}

	float time = 0.0f;
	sf::Texture texture;
};

class Animation
{
private:
	float time = 0.0f;
	float lenght;
	vector<AnimFrame> frames;
public:
	Animation(float lenght = 0.0f, vector<AnimFrame> frames = {});
	void Update(float deltaTime);

	sf::Texture GetTexture();
};

