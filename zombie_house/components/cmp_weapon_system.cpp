#include "cmp_weapon_system.h"
#include <SFML/Window/Keyboard.hpp>
using namespace std;
using namespace sf;

int WeaponSystemComponent::getWeapon()
{
	return weapon;
}

void WeaponSystemComponent::pickup(int weapon)
{
	if (weapon == 1)
	{
		has_pistol = true;
	}
	if (weapon == 2)
	{
		has_smg = true;
	}
	if (weapon == 3)
	{
		has_shotgun = true;
	}
	if (weapon == 4)
	{
		has_pistol = false;
		has_smg = false;
		has_shotgun = false;
		has_ar = true;
	}
}

void WeaponSystemComponent::select_weapon()
{
	if (Keyboard::isKeyPressed(Keyboard::Num1) && has_pistol == true)
	{
		weapon = 1;
		std::cout << "Weapon: 1";
	}
	if (Keyboard::isKeyPressed(Keyboard::Num2) && has_smg == true)
	{
		weapon = 2;
		std::cout << "Weapon: 2";
	}
	if (Keyboard::isKeyPressed(Keyboard::Num3) && has_shotgun == true)
	{
		weapon = 3;
		std::cout << "Weapon: 3";
	}
}

void WeaponSystemComponent::update(double dt)
{
	select_weapon();
}

WeaponSystemComponent::WeaponSystemComponent(Entity* p) : Component(p)
{
}
