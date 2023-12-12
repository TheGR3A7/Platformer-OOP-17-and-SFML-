#pragma once
#include <box2d/b2_world.h>
#include <box2d/b2_fixture.h>
#include "Renderer.h"
#include "Bullet.h"

class MyDebugDraw;
class Object;
class Character;

class ContactListener
{
public:
	virtual void OnBeginContact(b2Fixture* self, b2Fixture* other) = 0;
	virtual void OnEndContact(b2Fixture* self, b2Fixture* other) = 0;
};

enum class FixtureDataType
{
	Character,
	MapTile,
	Object,
};

struct FixtureData
{
	FixtureDataType type;
	ContactListener* listener;

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
	static b2World* world;
	static MyDebugDraw* debugDraw;

	static void Init();
	static void Update(float deltaTime);
	static void DebugDraw(Renderer& ren);
};

