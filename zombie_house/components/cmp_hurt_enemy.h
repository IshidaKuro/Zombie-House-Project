#pragma once
#include "cmp_physics.h"
#include <ecm.h>
#include <list>

class HurtEnemyComponent : public Component {
protected:
	std::weak_ptr<Entity> _enemy;

public:
  void update(double dt) override;
  void render() override {}
  explicit HurtEnemyComponent(Entity* p);
  HurtEnemyComponent() = delete;
};
