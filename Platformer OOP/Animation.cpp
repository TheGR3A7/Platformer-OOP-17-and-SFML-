#include "Animation.h"


Animation::Animation(float lenght, vector<AnimFrame> frames) : lenght(lenght), frames(frames)
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
		if (time >= frame.time) // ���� ����� ��������� � �������� ������� ��������(� ��������� �� ������)
			return frame.texture;
	}

	return sf::Texture();
}