#pragma once
#include "Animation.h"
#include "Object.h"
#include "Physics.h"
#include "Character.h"

class Enemy : public Object
{
private:
public:
    virtual void Begin() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render(Renderer& ren) = 0;
    virtual void Die() = 0;
    virtual bool IsDead() = 0;
    virtual void OnContact(b2Fixture* self, b2Fixture* other);
};

