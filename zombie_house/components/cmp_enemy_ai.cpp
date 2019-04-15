#include "cmp_enemy_ai.h"
#include<engine.h>

using namespace std;
using namespace sf;

bool pathing;
int random;
void EnemyAIComponent::update(double dt) {

	
	//check if the player is close to the zombie
	if (auto pl = _player.lock()) {
		if (length(pl->getPosition() - _parent->getPosition()) < 1000.0 && pathing == false)
		{
			//if they are, check if the zombie should path towards them

			//generate a random number between 1 and 20
			random = 1;
			//if the result is 1, then path towards the player
			if (random == 1)
			{
				//path towards the player
				pathing == true;
				cout << "pathing\n";
				//find which direction to move
				if (_parent->getPosition().x - pl->getPosition().x < 0)
					_direction = Vector2f(1.0f, 0);
				else
					_direction = Vector2f(-1.0f, 0);
				
			}
		}


	}
	//move in that direction 

	move(_direction * (float)(dt * _speed));
	ActorMovementComponent::update(dt);
}

EnemyAIComponent::EnemyAIComponent(Entity* p) : ActorMovementComponent(p), _player(_parent->scene->ents.find("player")[0])
{
	_direction = Vector2f(0, 0);
	_speed = 100.0f;

	
}
