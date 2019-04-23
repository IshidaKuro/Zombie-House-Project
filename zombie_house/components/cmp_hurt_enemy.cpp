#include "cmp_hurt_enemy.h"
#include "cmp_hp.h"
#include <engine.h>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

using namespace std;
using namespace sf;

sf::SoundBuffer buffer3;
sf::Sound sound3;

void HurtEnemyComponent::update(double dt) {
	//cout << "HP : " << hp;
	for (int i = 0; i < _parent->scene->ents.find("enemy").size(); i++)
	{
		
		if (auto pl = _enemy[i].lock())
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

					cout << "Play sound";

					//sound3.setBuffer(buffer3);
					//sound3.play();

				}

				setHP(getHP() - 1);
				if (getHP() <= 0)
				{
					pl->setForDelete();
					// _parent->setForDelete();
					cout << "Kill enemy";
					if (!buffer3.loadFromFile("res/sounds/zombie_dead.wav"))
					{
						cout << "Error loading zombie sound";
					}
					else
					{

						cout << "Play sound";

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

int HurtEnemyComponent::getHP()
{
	for (int i = 0; i < _parent->scene->ents.find("enemy").size(); i++)
	{
		auto en = _enemy[i].lock();
		int hp = en->GetCompatibleComponent<HPComponent>().at(0)->getHP();
		return hp;
	}
}

void HurtEnemyComponent::getEnemies()
{
	for (int i = 0; i < _parent->scene->ents.find("enemy").size(); i++)
	{
		_enemy[i] = _parent->scene->ents.find("enemy")[i];
	}
}

void HurtEnemyComponent::setHP(int in)
{
	for (int i = 0; i < _parent->scene->ents.find("enemy").size(); i++)
	{
		auto en = _enemy[i].lock();
		en->GetCompatibleComponent<HPComponent>().at(0)->setHP(in);
	}
}

HurtEnemyComponent::HurtEnemyComponent(Entity* p)
	: Component(p) {
}
