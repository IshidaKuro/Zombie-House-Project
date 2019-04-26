#include "cmp_persistence.h"
#include "cmp_pickup_ammo.h"
#include <iostream>
#include <fstream>
#include "engine.h"
#include "../game.h"
using namespace std;
using namespace sf;

void LoadFileComponent::update(double dt)
{
}

string LoadFileComponent::LoadFile(string fileToRead)
{
	string output;
	char c;
	ifstream loadFile;
	loadFile.open(fileToRead);
	if (loadFile.is_open())
	{
		while (loadFile.get(c))
		{
			output += c;
		}
	}
	else
	{
		cout << "No file";
	}

	loadFile.close();
	return output;
}

LoadFileComponent::LoadFileComponent(Entity* p)
	: Component(p) {}


void SaveFileComponent::update(double dt)
{
}

void SaveFileComponent::SaveFile(string level)
{
	ofstream saveFile;
	saveFile.open("ZombieHouseSaveFile.txt");
	if (saveFile.is_open())
	{
		saveFile << level;
	}
	saveFile.close();

	ofstream levelFile;
	levelFile.open("Level" + level + ".dat");
	if (levelFile.is_open())
	{
		levelFile << zombieKillCount << "," << ammoPickupCount;
	}
	levelFile.close();

	ofstream ammoFile;
	ammoFile.open("ammo.dat");
	if (ammoFile.is_open())
	{
		if (auto pl = _player.lock())
		{
			auto ammo = pl->GetCompatibleComponent<PickupAmmoComponent>().at(0);
			string p_ammo;
			string smg_ammo;
			string shotgun_ammo;
			if (ammo->getAmmo("pistol") < 10)
			{
				p_ammo = "0" + ammo->getAmmo("pistol");
			}
			if (ammo->getAmmo("smg") < 10)
			{
				smg_ammo = "0" + ammo->getAmmo("smg");
			}
			if (ammo->getAmmo("smg") < 10)
			{
				shotgun_ammo = "0" + ammo->getAmmo("shotgun");
			}
			ammoFile << ammo->getAmmo("pistol") << "," << ammo->getAmmo("smg") << "," << ammo->getAmmo("shotgun");
		}
	}
	ammoFile.close();
}

SaveFileComponent::SaveFileComponent(Entity * p)
	: Component(p), _player(_parent->scene->ents.find("player")[0]) {}
