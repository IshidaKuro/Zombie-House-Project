#pragma once
#include "cmp_physics.h"
#include <ecm.h>

class HPComponent : public Component {
protected:
	int hp;

public:
  void update(double dt) override;
  void render() override {}
  int getHP();
  explicit HPComponent(Entity* p, int hp = 3);
  HPComponent() = delete;
};
