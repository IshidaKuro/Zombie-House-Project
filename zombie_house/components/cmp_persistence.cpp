#include "cmp_persistence.h"
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

	//output = loadFile.get(output, 256);
	loadFile.close();
	//loadFile.open("ZombieHouseSaveFile.txt");
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

	ofstream levelFile;
	levelFile.open(level + ".dat");
	if (saveFile.is_open())
	{
		saveFile << level;
	}

	if (levelFile.is_open())
	{
		levelFile << zombieKillCount << "," << ammoPickupCount;
	}

	saveFile.close();
}

SaveFileComponent::SaveFileComponent(Entity * p)
	: Component(p), _player(_parent->scene->ents.find("player")[0]) {}
