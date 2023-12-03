#pragma once
#include <box2d/b2_world.h>

class Physics
{
public:
	static b2World world;

	static void Init();
	static void Update(float deltaTime);
};

