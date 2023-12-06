#pragma once
#include <box2d/b2_world.h>
#include <box2d/b2_fixture.h>
#include "Renderer.h"

class MyDebugDraw;
class Character;
class Object;

class ContactListener
{
public:
	virtual void OnBeginContact(b2Fixture* other) = 0;
	virtual void OnEndContact(b2Fixture* other) = 0;
};

enum class FixtureDataType
{
	Character,
	MapTile,
	Object
};

struct FixtureData
{
	ContactListener* listener;
	FixtureDataType type;

	union
	{
		Character* character;
		Object* object;
		struct { int mapX, mapY; };
	};
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

