#pragma once
#include "cmp_physics.h"
#include <ecm.h>
#include <list>

class PickupAmmoComponent : public Component {
protected:
	std::weak_ptr<Entity> _enemy;
	int pistolAmmo;
	int smgAmmo;
	int shotgunAmmo;

public:
	

  void update(double dt) override;
  void render() override {}
  int getAmmo(const std::string& type);
  void setAmmo(const std::string& type, int amount);
  explicit PickupAmmoComponent(Entity* p);
  PickupAmmoComponent() = delete;
};
