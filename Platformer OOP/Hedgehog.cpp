#define _USE_MATH_DEFINES
#include <cmath>
#include "Hedgehog.h"
#include "Game.h"
#include "Resources.h"
#include <box2d/b2_circle_shape.h>

void Hedgehog::Begin()
{
	walkAnimation = Animation(0.90f,
		{
			AnimFrame(0.75f, Resources::textures["h_walk6.png"]),
			AnimFrame(0.60f, Resources::textures["h_walk5.png"]),
			AnimFrame(0.45f, Resources::textures["h_walk4.png"]),
			AnimFrame(0.30f, Resources::textures["h_walk3.png"]),
			AnimFrame(0.15f, Resources::textures["h_walk2.png"]),
			AnimFrame(0.00f, Resources::textures["h_walk1.png"]),
		});
    sleepAnimation = Animation(0.80f,
        {
            AnimFrame(0.60f, Resources::textures["h_sleep4.png"]),
            AnimFrame(0.40f, Resources::textures["h_sleep3.png"]),
            AnimFrame(0.20f, Resources::textures["h_sleep2.png"]),
            AnimFrame(0.00f, Resources::textures["h_sleep1.png"]),
        });

	tag = "hedgehog";

	fixtureData.object = this;
	fixtureData.type = FixtureDataType::Object;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	body = Physics::world->CreateBody(&bodyDef);

	b2CircleShape circleShape;
	circleShape.m_radius = 0.5f;

	b2FixtureDef fixtureDef;
	fixtureDef.userData.pointer = (uintptr_t)&fixtureData;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f; // ������
	body->CreateFixture(&fixtureDef);
}

void Hedgehog::Update(float deltaTime)
{
    if (isDead)
    {
        Physics::world->DestroyBody(body);
        DeleteObject(this);
        return;
    }

    b2Vec2 velocity = body->GetLinearVelocity();

    if (isSleeping == false)
    {
        textureToDraw = walkAnimation.GetTexture();

        walkTimer += deltaTime;

        if (walkTimer >= walkDuration)
        {
            Sleep();
        }

        if (std::abs(velocity.x) == 0.00f)
        {
            movement *= -1.0f;
        }

        velocity.x = movement;

        if (velocity.x < 0.0f)
            dirLeft = true;
        else if (velocity.x > 0.0f)
            dirLeft = false;

        body->SetLinearVelocity(velocity);

        walkAnimation.Update(deltaTime);
    }
    else
    {
        textureToDraw = sleepAnimation.GetTexture();

        sleepTimer += deltaTime;

        if (sleepTimer >= sleepDuration)
        {
            WakeUp();
        }

        else
        {
            body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
        }
        sleepAnimation.Update(deltaTime);
    }

    position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
    angle = body->GetAngle() * (180.0f / M_PI);
}


void Hedgehog::Render(Renderer& ren)
{
	ren.Draw(textureToDraw, !isDead ? position : sf::Vector2f(position.x, position.y + 0.35f), sf::Vector2f(dirLeft ? -1.0f : 1.0f, isDead ? 0.4f : 1.0f), angle);
}

void Hedgehog::Die()
{
	isDead = true;
	//Physics::world->DestroyBody(body); 
}

bool Hedgehog::IsDead()
{
	return isDead;
}

void Hedgehog::OnContact(b2Fixture* self, b2Fixture* other)
{
    if (IsSleeping() == true)
    	Die();
    else if (!IsDead())
    {
        if (player.hasShield != 1 && player.immortalityTimer <= 0.0f)
            player.isDead = true;
        if (player.GetGroundFixture() != self && player.hasShield == 1)
        {
            player.hasShield += 1;
            player.immortalityTimer = 2.0f;
        }
    }
}

void Hedgehog::Sleep()
{
	isSleeping = true;
    sleepTimer = 0.0f;
}

void Hedgehog::WakeUp()
{
	isSleeping = false;
    walkTimer = 0.0f;

    movement *= -1.0;
}

bool Hedgehog::IsSleeping()
{
    return isSleeping;
}