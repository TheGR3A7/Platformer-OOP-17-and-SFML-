#pragma once

#include "Animation.h"
#include "Object.h"
#include "Physics.h"

class Enemy : public Object
{
private:
	Animation animation{};
	float movement = 5.0f;
	bool dirLeft = false;

	float destroyTimer = 0.0f;
	bool isDead = false;

	FixtureData fixtureData{};
	b2Body* body{};
public:
	virtual void Begin() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Renderer& ren) override;

	void Die();
};

