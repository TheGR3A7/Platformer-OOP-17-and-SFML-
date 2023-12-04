#pragma once
#include <box2d/b2_world.h>
#include "Renderer.h"

class MyDebugDraw;

class Physics
{
public:
	static b2World world;
	static MyDebugDraw* debugDraw;

	static void Init();
	static void Update(float deltaTime);
	static void DebugDraw(Renderer& ren);
};

