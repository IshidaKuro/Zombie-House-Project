#include "cmp_weapon_system.h"
#include <SFML/Window/Keyboard.hpp>
#include "cmp_bullet.h"
#include "engine.h"
#include <SFML/Graphics/CircleShape.hpp>
#include "cmp_hurt_enemy.h"

using namespace std;
using namespace sf;
float temp;
void WeaponSystemComponent::fire() const
{
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		auto bullet = _parent->scene->makeEntity();
		bullet->setPosition(_parent->getPosition());
		bullet->addComponent<HurtEnemyComponent>();
		bullet->addComponent<BulletComponent>();
		auto s = bullet->addComponent<ShapeComponent>();

		s->setShape<sf::CircleShape>(3.f);
		s->getShape().setFillColor(Color::Red);
		s->getShape().setOrigin(8.f, 8.f);
		auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(3.f, 0.f));
		p->setRestitution(.4f);
		p->setFriction(.005f);
		p->impulse(sf::rotate(Vector2f(10.f, 0.f), -_parent->getRotation()));
	}
}

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
	auto player = _parent->scene->makeEntity();
	auto p = _parent->GetCompatibleComponent<ShapeComponent>();

	if (Keyboard::isKeyPressed(Keyboard::Num1) && has_pistol == true)
	{
		p.at(0)->getShape().setFillColor(Color::Blue);
		weapon = 1;
		fire_rate = 0.5f;
		temp = fire_rate;
		std::cout << "Weapon: 1";
	}
	if (Keyboard::isKeyPressed(Keyboard::Num2) && has_smg == true)
	{
		p.at(0)->getShape().setFillColor(Color::Green);
		weapon = 2;
		fire_rate = 0.2f;
		temp = fire_rate;
		std::cout << "Weapon: 2";
	}
	if (Keyboard::isKeyPressed(Keyboard::Num3) && has_shotgun == true)
	{
		p.at(0)->getShape().setFillColor(Color::Yellow);
		weapon = 3;
		fire_rate = 2.0f;
		temp = fire_rate;
		std::cout << "Weapon: 3";
	}
}

void WeaponSystemComponent::update(double dt)
{
	select_weapon();
	
	fire_rate -= dt;
	if (fire_rate < 0.f) {
		fire();
		fire_rate = temp;
	}
}

WeaponSystemComponent::WeaponSystemComponent(Entity* p) : Component(p), fire_rate(0.5f)
{
}
