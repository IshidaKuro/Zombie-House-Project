#include "cmp_persistence.h"
#include <iostream>
#include <fstream>
#include "engine.h"
using namespace std;
using namespace sf;

void LoadFileComponent::LoadFile()
{
	ifstream loadFile;
	loadFile.open("ZombeHouseSaveFile");
}

LoadFileComponent::LoadFileComponent(Entity* p)
	: Component(p) {}

void SaveFileComponent::setLevel(string in)
{
	level = in;
}

void SaveFileComponent::update(double dt)
{
}

void SaveFileComponent::SaveFile()
{
	ofstream saveFile;
	saveFile.open("ZombieHouseSaveFile.txt");

	if (auto pl = _player.lock())
	{
		float xPos = pl->getPosition().x;
		float yPos = pl->getPosition().y;
		if (saveFile.is_open())
		{
			saveFile << level << "," << xPos << "," << yPos;
		}
	}

	saveFile.close();
}

SaveFileComponent::SaveFileComponent(Entity * p)
	: Component(p), _player(_parent->scene->ents.find("player")[0]) {}
