#pragma once
#include <box2d/b2_world.h>
#include "Renderer.h"

class MyDebugDraw;

class ContactListener
{
public:
	virtual void OnBeginContact() = 0;
	virtual void OnEndContact() = 0;
};

class Physics
{
public:
	static b2World world;
	static MyDebugDraw* debugDraw;

	static void Init();
	static void Update(float deltaTime);
	static void DebugDraw(Renderer& ren);
};

