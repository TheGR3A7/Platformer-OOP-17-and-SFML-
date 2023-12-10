#define _USE_MATH_DEFINES
#include <cmath>
#include "Game.h"
#include "Enemy.h"
#include "Resources.h"
#include <box2d/b2_circle_shape.h>

void Enemy::Begin()
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
	fixtureDef.friction = 0.0f; // трение
	body->CreateFixture(&fixtureDef);
}

void Enemy::Update(float deltaTime)
{
	if (isDead)
	{
		destroyTimer += deltaTime;
		if (destroyTimer >= 1.0f)
		{
			Physics::world->DestroyBody(body); // пофиксилось удаление
			DeleteObject(this);
		}
		return;
	}

	animation.Update(deltaTime);

	b2Vec2 velocity = body->GetLinearVelocity();

	if (abs(velocity.x == 0.00f))
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

void Enemy::Render(Renderer& ren)
{
	ren.Draw(animation.GetTexture(), !isDead ? position : sf::Vector2f(position.x, position.y + 0.35f), sf::Vector2f(dirLeft ? -1.0f : 1.0f, isDead ? 0.4f : 1.0f), angle);
}

void Enemy::Die() {
	isDead = true;
	//Physics::world->DestroyBody(body); 
}

bool Enemy::IsDead()
{
	return isDead;
}

