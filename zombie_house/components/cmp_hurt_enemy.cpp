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

  if (auto pl = _enemy.lock()) 
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

			sound3.setBuffer(buffer3);
			sound3.play();
			  
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

					  sound3.setBuffer(buffer3);
					  sound3.play();
				  
			  }
		  }
		  _parent->setForDelete();
		  //cout << "HP: " << hp;

	  }
  }
}

int HurtEnemyComponent::getHP()
{
	auto en = _enemy.lock();
	int hp = en->GetCompatibleComponent<HPComponent>().at(0)->getHP();
	return hp;
}

void HurtEnemyComponent::setHP(int in)
{
	auto en = _enemy.lock();
	en->GetCompatibleComponent<HPComponent>().at(0)->setHP(in);
}

HurtEnemyComponent::HurtEnemyComponent(Entity* p)
    : Component(p), _enemy(_parent->scene->ents.list.at(1)) {}
