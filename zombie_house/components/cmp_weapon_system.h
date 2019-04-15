#pragma once
#include <ecm.h>

class WeaponSystemComponent : public Component
{
protected:
	bool has_pistol = true;
	bool has_smg = true;
	bool has_shotgun = true;
	bool has_ar = false;

	int weapon;
	
	float fire_rate;
	void fire() const;

public:
	//1 pistol, 2 smg, 3 shotgun, 4 ar
	int getWeapon();
	void pickup(int weapon);
	void select_weapon();
	void update(double dt) override;
	void render() override {};
	WeaponSystemComponent() = delete;
	explicit WeaponSystemComponent(Entity* p);
};

