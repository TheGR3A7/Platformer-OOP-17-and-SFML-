#include "Animation.h"


Animation::Animation(float lenght, std::vector<AnimFrame> frames) : lenght(lenght), frames(frames)
{
}

void Animation::Update(float deltaTime)
{
	time += deltaTime;
}

sf::Texture Animation::GetTexture()
{
	while (time > lenght)
	{
		time -= lenght;
	}

	for (auto& frame : frames)
	{
		if (time >= frame.time) // надо будет указывать в обратном порядке текстуры(с последней на первую)
			return frame.texture;
	}

	return sf::Texture();
}