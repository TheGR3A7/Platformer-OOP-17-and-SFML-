#define _USE_MATH_DEFINES
#include "Character.h"
#include "Resources.h"
#include "Physics.h"
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <cmath>


const float movementSpeed = 3.0f;

void Character::Begin()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	body = Physics::world.CreateBody(&bodyDef);
	b2PolygonShape shape;
	shape.SetAsBox(0.5f, 1.0f);// половина размера Перса
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;// фигура
	fixtureDef.density = 1.0f; // плотность
	fixtureDef.friction = 0.3f; // трение
	body->CreateFixture(&fixtureDef);
}

void Character::Update(float deltaTime)
{
	float move = movementSpeed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		move *= 2;

	position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
	angle = body->GetAngle() * (180.0f / M_PI);

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	//	position.x += move * deltaTime;
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	//	position.x -= move * deltaTime;
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	//	position.y -= move * deltaTime;
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	//	position.y += move * deltaTime;
}

void Character::Draw(Renderer& ren)
{
	ren.Draw(Resources::textures["sand.png"], position, sf::Vector2f(1.0f, 2.0f), angle); // типо Перс 2 метра ростом и 1 метр в ширину(мы теперь делем исходные данные на 16)
}
