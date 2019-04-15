#include "cmp_enemy_ai.h"
#include<engine.h>

using namespace std;
using namespace sf;

void EnemyAIComponent::update(double dt) {

	auto mov = _direction * (float)(dt * _speed);
	mov.x += _direction.x * 16.f;
	if (!validMove(_parent->getPosition() + mov)) {
		_direction *= -1.f;
	}

	move(_direction * (float)(dt * _speed));
	ActorMovementComponent::update(dt);
}

EnemyAIComponent::EnemyAIComponent(Entity* p) : ActorMovementComponent(p) {
	_direction = Vector2f(0, 0);
	_speed = 100.0f;

	//check if the player is close to the zombie
	if (auto pl = _player.lock()) {
		if (length(pl->getPosition() - _parent->getPosition()) < 100.0)
		{
			//if they are, check if the zombie should path towards them

			//generate a random number between 1 and 0
			int random = rand() % 1;
			//if the result is 1, then path towards the player
			if (random == 1)
			{
				//path towards the player

				//find which direction to move
				if (_parent->getPosition().x - p->getPosition().x < 0)
					_direction = Vector2f(1.0f, 0);
				else
					_direction = Vector2f(-1.0f, 0);
				//move in that direction
			}
		}


	}
}
