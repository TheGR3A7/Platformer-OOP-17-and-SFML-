#pragma once
#include "Enemy.h"

class Duck : public Enemy
{
private:
	Animation animation;
	float movement = 5.0f;
	bool dirLeft = false;

	bool isDead = false;

	FixtureData fixtureData;
	b2Body* body;
public:
	virtual void Begin() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Renderer& ren) override;

	virtual void Die() override;
	virtual bool IsDead() override;
};

