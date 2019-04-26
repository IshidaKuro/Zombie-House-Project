#include "cmp_hurt_enemy.h"
#include "cmp_hp.h"
#include <engine.h>
#include "../game.h"
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

using namespace std;
using namespace sf;

sf::SoundBuffer buffer3;
sf::Sound sound3;

void HurtEnemyComponent::update(double dt) {
	//cout << "HP : " << hp;
	for (int i = 0; i < _enemies.size(); i++)
	{	
		if (auto pl = _enemies[i].en.lock())
		{
			if (length(pl->getPosition() - _parent->getPosition()) < 25.0)
			{
				//play sound
				if (!buffer3.loadFromFile("res/sounds/zombie_hurt.wav"))
				{
					cout << "Error loading zombie sound";
				}
				else
				{

					

					//sound3.setBuffer(buffer3);
					//sound3.play();

				}

				
				auto hpGet = pl->GetCompatibleComponent<HPComponent>().at(0);
				//int hp = hpGet->getHP();
				hpGet->setHP(hpGet->getHP() - 1);

				if (hpGet->getHP() <= 0)
				{
					zombieKillCount++;
					pl->setForDelete();
					_enemies.erase(i);
					// _parent->setForDelete();
					cout << "Kill enemy";
					if (!buffer3.loadFromFile("res/sounds/zombie_dead.wav"))
					{
						cout << "Error loading zombie sound";
					}
					else
					{

						

						//sound3.setBuffer(buffer3);
					   // sound3.play();

					}
				}
				_parent->setForDelete();
				//cout << "HP: " << hp;
			}
		}
    }
}

HurtEnemyComponent::HurtEnemyComponent(Entity* p)
	: Component(p){
}
