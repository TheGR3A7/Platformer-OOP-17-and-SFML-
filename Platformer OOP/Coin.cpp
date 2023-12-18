#include "Coin.h"
#include "Resources.h"
#include "Physics.h"
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <iostream>
#include "Game.h"


Coin::~Coin()
{
	Physics::world->DestroyBody(body);
}

void Coin::Begin()
{
    tag = "coin";

    animation = Animation(0.6f,
        {
            AnimFrame(0.5f, Resources::textures["coin1.png"]),
            AnimFrame(0.4f, Resources::textures["coin2.png"]),
            AnimFrame(0.3f, Resources::textures["coin3.png"]),
            AnimFrame(0.2f, Resources::textures["coin4.png"]),
            AnimFrame(0.1f, Resources::textures["coin5.png"]),
            AnimFrame(0.0f, Resources::textures["coin6.png"]),
        });

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


void Coin::Update(float deltaTime)
{
    if (isCollected)
    {
        destroyTimer += deltaTime;
        if (destroyTimer >= 0.1f)
        {
            Physics::world->DestroyBody(body); // пофиксилось удаление
            DeleteObject(this);
        }
        return;
    }

	animation.Update(deltaTime);
}

void Coin::Render(Renderer& ren)
{
	ren.Draw(animation.GetTexture(), position, sf::Vector2f(0.8f, 0.8f));
}

void Coin::OnContact(b2Fixture* self, b2Fixture* other)
{
    if (IsCollected())
        return;

    player.coinSound.play();
    Collected();
    //DeleteObject(data->object);
    cout << "coins = " << ++player.coins << endl;
}

void Coin::Collected()
{
    isCollected = true;
}

bool Coin::IsCollected()
{
    return isCollected;
}


