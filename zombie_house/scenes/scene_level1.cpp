//we need to use this as a template for other levels!!!!

#include "scene_level1.h"
#include "../components/cmp_enemy_ai.h"
#include "../components/cmp_enemy_turret.h"
#include "../components/cmp_hurt_player.h"
#include "../components/cmp_physics.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_persistence.h"
#include "../components/cmp_pickup_ammo.h"
#include "../game.h"
#include "system_resources.h"
#include "../components/cmp_weapon_system.h"
#include "../components/cmp_hp.h"
#include <LevelSystem.h>
#include <iostream>
#include <SFML/Audio/Music.hpp>
#include "../components/cmp_text.h"


using namespace std;
using namespace sf;
sf::Font font;
sf::Text text;
string playerAmmo;
static shared_ptr<Entity> player;
static shared_ptr<Entity> txt;

void Level1Scene::Load() {
	
		////cout << "Scene 1 Load" << endl;
		ls::loadLevelFile("res/levels/level_1.txt", 40.0f);
		auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
		ls::setOffset(Vector2f(0, ho));

		//load file - set game.h kill and ammo counts from file
		auto load = makeEntity();
		auto l = load->addComponent<LoadFileComponent>();
		string levelData = l->LoadFile("Level1.dat");
		//////cout << "LOADING DATA: " << out;
		if (levelData.size() <= 0)
		{
			zombieKillCount = 0;
			ammoPickupCount = 0;
		}
		else
		{
			zombieKillCount = levelData[0] - '0';
			ammoPickupCount = levelData[2] - '0';
		}

		string ammo = l->LoadFile("ammo.dat");
		string ps_ammo;
		int p_ammo;
		string ssmg_ammo;
		int smg_ammo;
		string sshotgun_ammo;
		int shotgun_ammo;
		if (ammo.size() > 0)
		{

			if (ammo[0] == 0)
			{
				p_ammo = ammo[1] - '0';
			}
			else
			{
				ps_ammo = to_string(ammo[0] - '0') + to_string(ammo[1] - '0');
				p_ammo = stoi(ps_ammo);
			}

			if (ammo[3] == 0)
			{
				smg_ammo = ammo[4] - '0';
			}
			else
			{
				ssmg_ammo = to_string(ammo[3] - '0') + to_string(ammo[4] - '0');
				smg_ammo = stoi(ssmg_ammo);
			}

			if (ammo[6] == 0)
			{
				shotgun_ammo = ammo[7] - '0';
			}
			else
			{
				sshotgun_ammo = to_string(ammo[6] - '0') + to_string(ammo[7] - '0');
				shotgun_ammo = stoi(sshotgun_ammo);
			}
		}
		else
		{
			p_ammo = 9;
			smg_ammo = 6;
			shotgun_ammo = 4;
		}
		//ALL ABOVE CODE MUST BE IN ALL SCENES EXCEPT THE ELSE DIRECTLY ABOVE = THIS IS LEVEL 1 SPECIFIC

		// Create player
		{
			// *********************************
			player = makeEntity();
			player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));

			player->addComponent<WeaponSystemComponent>();
			player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 30.f));
			// *********************************
			player->addTag("player");
			auto a = player->addComponent<PickupAmmoComponent>();
			a->setAmmo("pistol", p_ammo);
			a->setAmmo("smg", smg_ammo);
			a->setAmmo("shotgun", shotgun_ammo);
			shared_ptr<Texture> spriteSheet;

			spriteSheet = Resources::get<Texture>("player.png");

			auto pSprite = player->addComponent<SpriteComponent>();
			pSprite->setTexure(spriteSheet);
			pSprite->getSprite().scale(2.0f, 2.0f);
			pSprite->getSprite().setOrigin(10.f, 15.f);


		}
		//same as ammo needs done here
		auto enemySpawn = ls::findTiles(ls::ENEMY);
		for (int e = 0; e < zombieKillCount; e++)
		{
			enemySpawn.pop_back();
		}
		for (auto e : enemySpawn)
		{
			auto pos = ls::getTilePosition(e) + Vector2f(0, 25);
			auto enemy2 = makeEntity();
			enemy2->setPosition(pos);
			enemy2->addComponent<HurtComponent>();
			enemy2->addComponent<HPComponent>();
			// Add ShapeComponent, Red 16.f Circle

			enemy2->addTag("enemy");
			// Add EnemyAIComponent
			enemy2->addComponent<EnemyAIComponent>();
			shared_ptr<Texture> spriteSheet;

			spriteSheet = Resources::get<Texture>("zombie.png");

			auto eSprite = enemy2->addComponent<SpriteComponent>();
			eSprite->setTexure(spriteSheet);
			eSprite->getSprite().scale(2.0f, 2.0f);
			eSprite->getSprite().setOrigin(10.f, 15.f);
		}

		//create ammo objects
		{
			auto ammoCount = ls::findTiles(ls::AMMO);
			//remove based on loaded count
			for (int c = 0; c < ammoPickupCount; c++)
			{
				ammoCount.pop_back();
			}

			for (auto a : ammoCount)
			{
				auto pos = ls::getTilePosition(a) + Vector2f(0, 34);
				auto ammo = makeEntity();
				ammo->setPosition(pos);
				ammo->addTag("ammo");
				shared_ptr<Texture> spriteSheet;

				spriteSheet = Resources::get<Texture>("ammo.png");

				auto aSprite = ammo->addComponent<SpriteComponent>();
				aSprite->setTexure(spriteSheet);
				aSprite->getSprite().scale(2.0f, 2.0f);
				aSprite->getSprite().setOrigin(10.f, 15.f);
			}
			// *********************************

		}

		// Add physics colliders to level tiles.
		{
			// *********************************
			auto walls = ls::findTiles(ls::WALL);
			for (auto w : walls) {
				auto pos = ls::getTilePosition(w);
				pos += Vector2f(20.f, 20.f); //offset to center
				auto e = makeEntity();
				e->setPosition(pos);
				e->addComponent<PhysicsComponent>(false, Vector2f(40.f, 40.f));
			}
			// *********************************
		}
		for (int i = 0; i < ents.find("enemy").size(); i++)
		{
			Enemies ens;
			ens.en = ents.find("enemy").at(i);
			_enemies[i] = ens;
		}
		for (int i = 0; i < ents.find("ammo").size(); i++)
		{
			Ammo amm;
			amm.am = ents.find("ammo").at(i);
			_ammo[i] = amm;
		}
		auto door = makeEntity();
		door->setPosition(ls::getTilePosition(ls::findTiles(ls::END)[0]) + Vector2f(0, -25));

		shared_ptr<Texture> spriteSheet;

		spriteSheet = Resources::get<Texture>("door.png");

		auto dSprite = door->addComponent<SpriteComponent>();
		dSprite->setTexure(spriteSheet);
		dSprite->getSprite().scale(2.0f, 2.0f);

		////cout << " Scene 1 Load Done" << endl;
		{
		}
	
  
  setLoaded(true);
}

void Level1Scene::UnLoad() {
  ////cout << "Scene 1 UnLoad" << endl;
  player.reset();
  ls::unload();
  Scene::UnLoad();
}

void Level1Scene::Update(const double& dt) {
  Scene::Update(dt);

  const auto pp = player->getPosition();
  if (ls::getTileAt(pp) == ls::END) {
    Engine::ChangeScene((Scene*)&level2);
  } else if (!player->isAlive()) {
    Engine::ChangeScene((Scene*)&level1);
  }
  if (Keyboard::isKeyPressed(Keyboard::S))
  {
	  //THIS CODE MUST BE IN ALL SCENES
	  auto save = makeEntity();
	  auto s = save->addComponent<SaveFileComponent>();
	  s->SaveFile("1");
	  Engine::ChangeScene(&menu);
  }


  
}

void Level1Scene::Render() {
  ls::render(Engine::GetWindow());
  Scene::Render();
}
