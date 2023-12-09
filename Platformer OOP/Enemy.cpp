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

	b2BodyDef bodyDef{};
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	body = Physics::world.CreateBody(&bodyDef);

	b2CircleShape circleShape{};
	circleShape.m_radius = 0.5f;

	b2FixtureDef fixtureDef{};
	fixtureDef.userData.pointer = (uintptr_t)&fixtureData;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f; // трение
	body->CreateFixture(&fixtureDef);
}

void Enemy::Update(float deltaTime)
{
	animation.Update(deltaTime);
}

void Enemy::Render(Renderer& ren)
{
	ren.Draw(animation.GetTexture(), position, sf::Vector2f(1.0f, 1.0f), angle);
}


