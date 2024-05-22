#pragma once
#include "Renderer.h"
#include "Physics.h"

using namespace std;

class Object
{
public:
	sf::Vector2f position;
	float angle;
	string tag;

	virtual void Begin() {}
	virtual void Update(float deltaTime) {}
	virtual void Render(Renderer& ren) {}
	virtual void OnContact(b2Fixture* self, b2Fixture* other) {}
	virtual void OnEndContact(b2Fixture* self, b2Fixture* other) {}
};

