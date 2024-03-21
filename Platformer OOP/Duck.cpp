#define _USE_MATH_DEFINES
#include "Duck.h"
#include <cmath>
#include "Game.h"
#include "Resources.h"
#include <box2d/b2_circle_shape.h>

void Duck::Begin()
{
	animation = Animation(0.80f,
		{
			AnimFrame(0.60f, Resources::textures["d_walk4.png"]),
			AnimFrame(0.40f, Resources::textures["d_walk3.png"]),
			AnimFrame(0.20f, Resources::textures["d_walk2.png"]),
			AnimFrame(0.00f, Resources::textures["d_walk1.png"]),
		});

	tag = "enemy";

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

void Duck::Update(float deltaTime)
{
	if (isDead)
	{
		Physics::world->DestroyBody(body); // ����������� ��������
		DeleteObject(this);
		return;
	}

	animation.Update(deltaTime);

	b2Vec2 velocity = body->GetLinearVelocity();

	if (abs(velocity.x) == 0.0f)
		movement *= -1.0f;

	velocity.x = movement;

	if (velocity.x < 0.0f)
		dirLeft = true;
	else if (velocity.x > 0.0f)
		dirLeft = false;

	body->SetLinearVelocity(velocity);

	position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
	angle = body->GetAngle() * (180.0f / M_PI);
}

void Duck::Render(Renderer& ren)
{
	ren.Draw(animation.GetTexture(), !isDead ? position : sf::Vector2f(position.x, position.y + 0.35f), sf::Vector2f(dirLeft ? -1.0f : 1.0f, isDead ? 0.4f : 1.0f), angle);
}

void Duck::Die() 
{
	isDead = true;
	//Physics::world->DestroyBody(body); 
}

bool Duck::IsDead()
{
	return isDead;
}