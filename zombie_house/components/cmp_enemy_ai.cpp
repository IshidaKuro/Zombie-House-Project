#include "cmp_enemy_ai.h"
#include <engine.h>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

using namespace std;
using namespace sf;

bool pathing = false;
int random;
sf::SoundBuffer buffer;
sf::Sound sound;
float wait = 0.02f;

void EnemyAIComponent::update(double dt) {

	
		//check if the player is close to the zombie
		if (auto pl = _player.lock()) {
			
			if (length(pl->getPosition() - _parent->getPosition()) > 200.0) //if the player is outside the zombie's view
			{
				_direction = Vector2f(0, 0); // make the zombie stand still
				pathing = false; // set pathing to false again

			}
			else
			{

				if (!pathing)
				{
	
					//generate a random number between 1 and 200
					random = rand() % 199 + 1;
					//if the result is 1, then path towards the player
					if (random == 1)
					{

						//play sound
						if (!buffer.loadFromFile("res/sounds/zombie_moan.wav"))
						{
							cout << "Error loading zombie sound";
						}
						else
						{
							wait -= dt;
							if (wait <= 0.f)
							{
								;
								sound.setBuffer(buffer);
								sound.play();
								wait = 0.02f;
							}
						}

						//path towards the player
						pathing == true;

						//find which direction to move
						if (_parent->getPosition().x - pl->getPosition().x < 0)
							_direction = Vector2f(1.0f, 0);
						else
							_direction = Vector2f(-1.0f, 0);
	
					}
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
	_speed = 70.0f;

	
}
