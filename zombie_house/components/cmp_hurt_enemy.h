#pragma once
#include "cmp_physics.h"
#include <ecm.h>
#include <list>

class HurtEnemyComponent : public Component {
protected:
	std::weak_ptr<Entity> _enemy[10];


public:
  void update(double dt) override;
  void render() override {}
  int getHP();
  void getEnemies();
  void setHP(int in);
  explicit HurtEnemyComponent(Entity* p);
  HurtEnemyComponent() = delete;
};
