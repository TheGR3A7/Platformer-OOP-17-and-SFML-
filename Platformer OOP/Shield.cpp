#include "Shield.h"
#include "Resources.h"
#include "Physics.h"
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <iostream>
#include "Game.h"
#include "Character.h"


Shield::~Shield()
{
    Physics::world->DestroyBody(body);
}

void Shield::Begin()
{
    tag = "shield";

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


void Shield::Update(float deltaTime)
{
    if (player.hasShield>1)
    {
        isCollected = false;
        Physics::world->DestroyBody(body);
        DeleteObject(this);
        player.hasShield = 0;
    }
    if (isCollected)
    {
        position.x = player.position.x;
        position.y = player.position.y - 0.4f;
    }
}

void Shield::Render(Renderer& ren)
{
    ren.Draw(Resources::textures["shield.png"], sf::Vector2f(position.x, position.y), sf::Vector2f(2.1f, 2.1f), angle);
}

void Shield::OnContact(b2Fixture* self, b2Fixture* other)
{
    if (IsCollected())
        return;

    Collected();
}

void Shield::Collected()
{
    isCollected = true;
    player.hasShield += 1;
}

bool Shield::IsCollected()
{
    return isCollected;
}