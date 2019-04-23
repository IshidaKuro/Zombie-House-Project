#include "cmp_weapon_system.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Joystick.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "cmp_bullet.h"
#include "engine.h"
#include <SFML/Graphics/CircleShape.hpp>
#include "cmp_hurt_enemy.h"
#include "../game.h"

using namespace std;
using namespace sf;
float temp;
sf::SoundBuffer buffer2;
sf::Sound sound2;
void WeaponSystemComponent::fire() const
{
	if (Keyboard::isKeyPressed(m_keys["Shoot"].key_pressed) || Joystick::isButtonPressed(0, m_keys["Joy_Shoot"].key_pressed))
	{
		if (weapon == 3)
		{
			auto bullet = _parent->scene->makeEntity();
			bullet->setPosition(_parent->getPosition());
			bullet->addComponent<HurtEnemyComponent>();
			bullet->addComponent<BulletComponent>();
			auto b1 = bullet->addComponent<ShapeComponent>();
			b1->setShape<sf::CircleShape>(3.f);
			b1->getShape().setFillColor(Color::Red);
			b1->getShape().setOrigin(8.f, 8.f);
			auto p = bullet->addComponent<PhysicsComponent>(true, Vector2f(3.f, 0.f));
			p->setRestitution(.4f);
			p->setFriction(.005f);
			p->impulse(sf::rotate(Vector2f(20.f, 0.f), -_parent->getRotation()));

			auto bullet2 = _parent->scene->makeEntity();
			bullet2->setPosition(_parent->getPosition());
			bullet2->addComponent<HurtEnemyComponent>();
			bullet2->addComponent<BulletComponent>();
			auto b2 = bullet2->addComponent<ShapeComponent>();
			b2->setShape<sf::CircleShape>(3.f);
			b2->getShape().setFillColor(Color::Yellow);
			b2->getShape().setOrigin(8.f, 8.f);
			auto p2 = bullet2->addComponent<PhysicsComponent>(true, Vector2f(30.f, 0.f));
			p2->setRestitution(.4f);
			p2->setFriction(.005f);
			p2->impulse(sf::rotate(Vector2f(20.f, 0.f), -_parent->getRotation()));


			auto bullet3 = _parent->scene->makeEntity();
			bullet3->setPosition(_parent->getPosition());
			bullet3->addComponent<HurtEnemyComponent>();
			bullet3->addComponent<BulletComponent>();
			auto b3 = bullet3->addComponent<ShapeComponent>();
			b3->setShape<sf::CircleShape>(3.f);
			b3->getShape().setFillColor(Color::Blue);
			b3->getShape().setOrigin(8.f, 8.f);
			auto p3 = bullet3->addComponent<PhysicsComponent>(true, Vector2f(80.f, 0.f));
			p3->setRestitution(.4f);
			p3->setFriction(.005f);
			p3->impulse(sf::rotate(Vector2f(20.f, 0.f), -_parent->getRotation()));

			//play sound
			if (!buffer2.loadFromFile("res/sounds/shotgun.wav"))
			{
				cout << "Error loading zombie sound";
			}
			else
			{
				cout << "Play sound";
				sound2.setBuffer(buffer2);
				sound2.play();
			}
		}
		else if (weapon == 1)
		{
			auto bullet = _parent->scene->makeEntity();
			bullet->addTag("bullet");
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

			//play sound
			if (!buffer2.loadFromFile("res/sounds/pistol.wav"))
			{
				cout << "Error loading zombie sound";
			}
			else
			{
				cout << "Play sound";
				sound2.setBuffer(buffer2);
				sound2.play();
			}
		}
		else if (weapon == 2)
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

			//play sound
			if (!buffer2.loadFromFile("res/sounds/smg.wav"))
			{
				cout << "Error loading zombie sound";
			}
			else
			{
				cout << "Play sound";
				sound2.setBuffer(buffer2);
				sound2.play();
			}
		}
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
		fire_rate = 1.0f;
		temp = fire_rate;
		std::cout << "Weapon: 3";
	}
}

void WeaponSystemComponent::update(double dt)
{
	select_weapon();
	
	if(weapon == 1 || weapon == 2 || weapon == 3)
	{ 
		fire_rate -= dt;
		if (fire_rate < 0.f) {
			fire();
			fire_rate = temp;
		}
	}
}

WeaponSystemComponent::WeaponSystemComponent(Entity* p) : Component(p), fire_rate(0.5f)
{
}
