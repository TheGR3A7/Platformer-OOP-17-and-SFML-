#define _USE_MATH_DEFINES
#include <cmath>
#include "Game.h"
#include "Enemy.h"
#include "Resources.h"
#include <box2d/b2_circle_shape.h>

void Enemy::OnContact(b2Fixture* self, b2Fixture* other)
{
	if (player.GetGroundFixture() == self)
		Die();
	else if (!IsDead())
		player.isDead = true;
}
