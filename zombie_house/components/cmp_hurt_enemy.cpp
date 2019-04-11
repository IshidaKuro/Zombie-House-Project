#include "cmp_hurt_enemy.h"
#include <engine.h>

using namespace std;
using namespace sf;

void HurtEnemyComponent::update(double dt) {
  if (auto pl = _enemy.lock()) 
  {
	  if (length(pl->getPosition() - _parent->getPosition()) < 25.0 && hp != 0) {
		  pl->setForDelete();
		  _parent->setForDelete();
	  }
  }
}

HurtEnemyComponent::HurtEnemyComponent(Entity* p)
    : Component(p), _enemy(_parent->scene->ents.list.at(1)) {}
