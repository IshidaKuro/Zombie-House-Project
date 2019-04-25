#pragma once
#include "cmp_physics.h"
#include <ecm.h>
#include <list>

class PickupAmmoComponent : public Component {
protected:
	std::weak_ptr<Entity> _enemy;


public:
  void update(double dt) override;
  void render() override {}
  void getAmmo();
  explicit PickupAmmoComponent(Entity* p);
  PickupAmmoComponent() = delete;
};
