#include "cmp_hurt_enemy.h"
#include "cmp_hp.h"
#include <engine.h>

using namespace std;
using namespace sf;

void HurtEnemyComponent::update(double dt) {
	//cout << "HP : " << hp;

  if (auto pl = _enemy.lock()) 
  {
	  //auto health = pl->GetCompatibleComponent<HPComponent>().at(0);
	  if (length(pl->getPosition() - _parent->getPosition()) < 25.0) 
	  {
		  _parent->setForDelete();
		  //cout << "HP: " << hp;

		pl->setForDelete();
		// _parent->setForDelete();
		cout << "KIll enemy";
		  
		  

	  }
  }
}

HurtEnemyComponent::HurtEnemyComponent(Entity* p)
    : Component(p), _enemy(_parent->scene->ents.list.at(1)) {}
