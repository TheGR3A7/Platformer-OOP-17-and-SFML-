#define _USE_MATH_DEFINES
#include "Character.h"
#include "Resources.h"
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_fixture.h>
#include <cmath>


const float movementSpeed = 7.0f;
const float jumpVelocity = 10.0f;

void Character::Begin()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true; // убирает вращение персонажа
	body = Physics::world.CreateBody(&bodyDef);


	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.0f; // плотность
	fixtureDef.friction = 0.0f; // трение

	b2CircleShape circleShape;
	circleShape.m_radius = 0.5f;
	circleShape.m_p.Set(0.0f, -0.5f);
	fixtureDef.shape = &circleShape;
	body->CreateFixture(&fixtureDef);

	circleShape.m_p.Set(0.0f, 0.5f);
	body->CreateFixture(&fixtureDef);

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(0.5f, 0.5f);
	fixtureDef.shape = &polygonShape;// фигура
	body->CreateFixture(&fixtureDef);

	polygonShape.SetAsBox(0.4f, 0.2f, b2Vec2(0.0f, 1.0f), 0.0f);
	fixtureDef.userData.pointer = (uintptr_t)this;
	fixtureDef.isSensor = true;
	body->CreateFixture(&fixtureDef);
}

void Character::Update(float deltaTime)
{
	float move = movementSpeed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		move *= 2;

	b2Vec2 velocity = body->GetLinearVelocity();
	velocity.x = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		velocity.x += move;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		velocity.x -= move;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isGrounded)
		velocity.y -= jumpVelocity;


	if (velocity.x < 0.0f)
		dirLeft = true;
	else if (velocity.x > 0.0f) // else if потому что если == 0, то он не должен менять сторону, при просто else это не учтется
		dirLeft = false;


	body->SetLinearVelocity(velocity);

	position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
	angle = body->GetAngle() * (180.0f / M_PI);

}

void Character::Draw(Renderer& ren)
{
	ren.Draw(Resources::textures["sand.png"], position, sf::Vector2f(dirLeft ? -1.0f : 1.0f, 2.0f), angle); // типо Перс 2 метра ростом и 1 метр в ширину(мы теперь делем исходные данные на 16)
}

void Character::OnBeginContact()
{
	isGrounded++;
}

void Character::OnEndContact()
{
	if (isGrounded > 0)
		isGrounded--;
}
