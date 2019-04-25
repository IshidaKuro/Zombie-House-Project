#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../components/cmp_physics.h"
#include "../components/cmp_player_physics.h"
#include "../game.h"
#include "../components/cmp_persistence.h"
#include "../components/cmp_weapon_system.h"
#include "../components/cmp_hp.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <LevelSystem.h>


using namespace std;
using namespace sf;
static shared_ptr<Entity> player;
std::map<std::string, MyKeys> m_keys;
std::map<std::int8_t, Enemies> _enemies;
std::map<std::int8_t, Ammo> _ammo;
int zombieKillCount;
int ammoPickupCount;
string out_level;

void MenuScene::Load() {
  cout << "Menu Load \n";
  //load file - set game.h kill and ammo counts from file

  auto load = makeEntity();
  auto l = load->addComponent<LoadFileComponent>();
  string levelData = l->LoadFile("Menu.dat");
  //cout << "LOADING DATA: " << out;
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


  string prev_level = l->LoadFile("ZombieHouseSaveFile.txt");
  if (prev_level.size() > 0)
  {
	   out_level = prev_level[5];
  }


  {
    auto txt = makeEntity();
    auto t = txt->addComponent<TextComponent>(
		
        "Platformer\nInteract (E) with the door to start/continue\nPress F1 to enter fullscreen\nInteract with blue square to remap controls");
  }

  if (ctrl_change == false)
  {
	  MyKeys key;
	  key.key_pressed = Keyboard::Left;
	  m_keys["Left"] = key;
	  key.key_pressed = Keyboard::Right;
	  m_keys["Right"] = key;
	  key.key_pressed = Keyboard::Space;
	  m_keys["Shoot"] = key;
  }

  cout << " Scene 1 Load" << endl;
  ls::loadLevelFile("res/levels/menu.txt", 40.0f);

  auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
  ls::setOffset(Vector2f(0, ho));

  // Create player
  {
	  player = makeEntity();
	  player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));

	  //shared_ptr<Texture> ss;
	  //if (!ss->loadFromFile("res/sprites/1.png")) {
	  //	cerr << "Failed to load spritesheet!" << std::endl;
	  //}
	  //auto sp = player->addComponent<SpriteComponent>();
	  //sp->setTexure(ss);
	  auto s = player->addComponent<ShapeComponent>();
	  s->setShape<sf::RectangleShape>(Vector2f(20.f, 30.f));
	  s->getShape().setFillColor(Color::Magenta);
	  s->getShape().setOrigin(10.f, 15.f);

	  player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 30.f));
	  player->addComponent<WeaponSystemComponent>();
  }

  // Add physics colliders to level tiles.
  {
	  auto walls = ls::findTiles(ls::WALL);
	  for (auto w : walls) {
		  auto pos = ls::getTilePosition(w);
		  pos += Vector2f(20.f, 20.f); //offset to center
		  auto e = makeEntity();
		  e->setPosition(pos);
		  e->addComponent<PhysicsComponent>(false, Vector2f(40.f, 40.f));
	  }
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

  setLoaded(true);
}

void MenuScene::Update(const double& dt) {
  // cout << "Menu Update "<<dt<<"\n";

	if (ls::getTileAt(player->getPosition()) == ls::END && Keyboard::isKeyPressed(Keyboard::E)) {
		if (out_level != "")
		{
			if (out_level == "2")
			{
				Engine::ChangeScene(&level2);
			}
			else if(out_level == "3")
			{
				Engine::ChangeScene(&level3);
			}
			
		}
		else
		{
			Engine::ChangeScene((Scene*)&level2);
		}
	}

  Scene::Update(dt);
}

void MenuScene::UnLoad()
{
	cout << "Scene 1 Unload" << endl;
	player.reset();
	ls::unload();
	Scene::UnLoad();
}

void MenuScene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}