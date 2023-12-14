#include "Flag.h"
#include "Resources.h"
#include "Physics.h"
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>

void Flag::Begin()
{
	tag = "flag";

	activeAnimation = Animation(1.0f,
		{
			AnimFrame(0.9f, Resources::textures["flag10.png"]),
			AnimFrame(0.8f, Resources::textures["flag9.png"]),
			AnimFrame(0.7f, Resources::textures["flag8.png"]),
			AnimFrame(0.6f, Resources::textures["flag7.png"]),
			AnimFrame(0.5f, Resources::textures["flag6.png"]),
			AnimFrame(0.4f, Resources::textures["flag5.png"]),
			AnimFrame(0.3f, Resources::textures["flag4.png"]),
			AnimFrame(0.2f, Resources::textures["flag3.png"]),
			AnimFrame(0.1f, Resources::textures["flag2.png"]),
			AnimFrame(0.0f, Resources::textures["flag1.png"]),
		});


	fixtureData.object = this;
	fixtureData.type = FixtureDataType::Object;

	b2BodyDef bodyDef;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	body = Physics::world->CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(0.25f, 0.25f); // поменять

	b2FixtureDef fixtureDef;
	fixtureDef.userData.pointer = (uintptr_t)&fixtureData;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f; // трение
	body->CreateFixture(&fixtureDef);

	body->SetTransform(b2Vec2(position.x - 0.25, position.y + 0.25f), angle); // сместил хитбок на 0.25 вниз и влево
}

void Flag::Update(float deltaTime)
{
	activeAnimation.Update(deltaTime);
}


void Flag::Render(Renderer& ren)
{
	ren.Draw(activeAnimation.GetTexture(), sf::Vector2f(position.x, position.y - 1.0f), sf::Vector2f(1.0f, 3.0f), angle);
}
