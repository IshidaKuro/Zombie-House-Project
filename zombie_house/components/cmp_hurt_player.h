#pragma once
#include "cmp_physics.h"
#include <ecm.h>_

class HurtComponent : public Component {
protected:
  std::weak_ptr<Entity> _player;

public:
  void update(double dt) override;
  void render() override {}
  explicit HurtComponent(Entity* p);
  HurtComponent() = delete;
};
