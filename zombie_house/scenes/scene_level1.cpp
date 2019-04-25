#include "scene_level1.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_weapon_system.h"
#include "../components/cmp_pickup_ammo.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include <list>
#include <SFML/Audio/Music.hpp>
#include "../components/cmp_enemy_ai.h"
#include "../components/cmp_hurt_player.h"
#include "../components/cmp_physics.h"
#include "../components/cmp_hp.h"
#include <SFML/Audio/Music.hpp>

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;

void Level1Scene::Load() {
  cout << " Scene 1 Load" << endl;
  ls::loadLevelFile("res/levels/level_1.txt", 40.0f);

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
	player->addComponent<PickupAmmoComponent>();
  }

  //create ammo objects
  {
	  auto ammo = makeEntity();
	  ammo->setPosition(ls::getTilePosition(ls::findTiles(ls::AMMO)[0]) +
		  Vector2f(0, 24));
	  // *********************************
	 
	  auto sAmmo = ammo->addComponent<ShapeComponent>();
	  sAmmo->setShape<sf::CircleShape>(8.0f);
	  sAmmo->getShape().setFillColor(Color::White);
	  ammo->addTag("ammo");
	  // *********************************
  
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

  //add background music
  {
	  Music music;
	  if (!music.openFromFile("res/sounds/background.wav"))
	  {
		  cout << "Error loading music";
	  }
	  else
	  {
		  music.play();
	  }
  }

  //Simulate long loading times
  {
	  //std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	  //load a loading screen scene?
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
  cout << " Scene 1 Load Done" << endl;
  setLoaded(true);

}

void Level1Scene::UnLoad() {
  cout << "Scene 1 Unload" << endl;
  player.reset();
  ls::unload();
  Scene::UnLoad();
}

void Level1Scene::Update(const double& dt) {

	if (ls::getTileAt(player->getPosition()) == ls::END && Keyboard::isKeyPressed(Keyboard::E)) {
    Engine::ChangeScene((Scene*)&level1);
  }

	
  Scene::Update(dt);
}

void Level1Scene::Render() {
  ls::render(Engine::GetWindow());
  Scene::Render();
}
