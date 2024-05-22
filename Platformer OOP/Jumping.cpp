#include "Jumping.h"
#include "Resources.h"
#include "Physics.h"
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <iostream>
#include "Game.h"
#include "Character.h"


Jumping::~Jumping()
{
    Physics::world->DestroyBody(body);
}

void Jumping::Begin()
{
    tag = "jumping";

    b2BodyDef bodyDef;
    bodyDef.position.Set(position.x, position.y);
    body = Physics::world->CreateBody(&bodyDef);
    b2PolygonShape shape;
    shape.SetAsBox(0.4f, 0.4f);

    FixtureData* fixtureData = new FixtureData();
    fixtureData->type = FixtureDataType::Object;
    fixtureData->object = this;

    b2FixtureDef fixtureDef;
    fixtureDef.userData.pointer = (uintptr_t)fixtureData;
    fixtureDef.isSensor = true;
    fixtureDef.density = 0.0f;
    fixtureDef.shape = &shape;
    body->CreateFixture(&fixtureDef);
}


void Jumping::Update(float deltaTime)
{
    if (isCollected)
    {
        boostTimer += deltaTime;
        if (boostTimer >= 5.0f)
        {
            player.SetJumpVelocity(15.0f);
            Physics::world->DestroyBody(body); 
            DeleteObject(this);
        }
    }
}

void Jumping::Render(Renderer& ren)
{
    ren.Draw(Resources::textures["jumpboost.png"], sf::Vector2f(position.x, position.y), sf::Vector2f(0.9f, 0.9f), angle);
}

void Jumping::OnContact(b2Fixture* self, b2Fixture* other)
{
    if (IsCollected())
        return;

    Collected();

    player.SetJumpVelocity(25.0f);
}

void Jumping::Collected()
{
    position.x = 200;
    position.y = 200;
    isCollected = true;
    boostTimer = 0.0f;
}

bool Jumping::IsCollected()
{
    return isCollected;
}