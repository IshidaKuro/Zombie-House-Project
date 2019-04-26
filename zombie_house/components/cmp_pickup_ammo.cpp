#include "cmp_pickup_ammo.h"
#include "cmp_hp.h"
#include <engine.h>
#include "../game.h"


using namespace std;
using namespace sf;

int ammoRand;

void PickupAmmoComponent::update(double dt) {
	//cout << "HP : " << hp;
	for (int i = 0; i < _ammo.size(); i++)
	{	
		if (auto ammo = _ammo[i].am.lock())
		{
				if (length(ammo->getPosition() - _parent->getPosition()) < 25.0 && Keyboard::isKeyPressed(Keyboard::E))
				{
					ammo->setForDelete();

					ammoPickupCount++;
					

					ammoRand = rand() % 30 + 1;

					if (ammoRand == 0)
					{
						//create a zombie
						cout << "zombie created" << endl;
					}
					else if (0 < ammoRand && ammoRand <= 12)
					{
						//add some pistol ammo to the player's inventory

						setAmmo("pistol", getAmmo("pistol") + rand() % 7 + 3);
						cout << "pistol ammo collected" << endl;
						cout <<"Pistol Ammo: "<< getAmmo("pistol");
					}
					else if (12 < ammoRand && ammoRand <= 22)
					{
						//add some SMG ammo to the player's inventory
						cout << "smg ammo collected" << endl;
					}
					else if (22 < ammoRand && ammoRand <= 30)
					{
						//add some shotgun ammo to the player's inventory
						cout << "shotgun ammo collected" << endl;
					}
					else
					{
						cout << "random number generator error " << ammoRand << endl;
					}

				}
			}
		}
  }

int PickupAmmoComponent::getAmmo(const std::string& type)
{
	
	if (type == "pistol") { return pistolAmmo; }
	if (type == "smg") { return smgAmmo; }
	if (type == "shotgun") { return shotgunAmmo; }
}

void PickupAmmoComponent::setAmmo(const std::string& type, int amount)
{
	if (type == "pistol") { pistolAmmo = amount; }
	if (type == "smg") { smgAmmo = amount; }
	if (type == "shotgun") { shotgunAmmo = amount; }

}


PickupAmmoComponent::PickupAmmoComponent(Entity* p)
	: Component(p){
}
