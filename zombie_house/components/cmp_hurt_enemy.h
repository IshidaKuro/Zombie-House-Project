#pragma once
#include "cmp_physics.h"
#include <ecm.h>

class HurtEnemyComponent : public Component {
protected:
  std::weak_ptr<Entity> _enemy;
public:
  void update(double dt) override;
  void render() override {}
  int getHP();
  void setHP(int in);
  explicit HurtEnemyComponent(Entity* p);
  HurtEnemyComponent() = delete;
};
