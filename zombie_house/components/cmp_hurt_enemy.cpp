#include "cmp_hurt_enemy.h"
#include "cmp_hp.h"
#include <engine.h>

using namespace std;
using namespace sf;

void HurtEnemyComponent::update(double dt) {
	//cout << "HP : " << hp;

  if (auto pl = _enemy.lock()) 
  {
	  if (length(pl->getPosition() - _parent->getPosition()) < 25.0) 
	  {
		  setHP(getHP() - 1);
		  if (getHP() <= 0)
		  {
			  pl->setForDelete();
			  // _parent->setForDelete();
			  cout << "Kill enemy";
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
