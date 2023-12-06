#pragma once
#include "Object.h"
#include "Animation.h"

class Coin : public Object
{
private:
	Animation animation;
public:
	virtual void Begin() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Renderer& ren) override;
};

