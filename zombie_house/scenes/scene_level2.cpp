#include "scene_level2.h"
#include "../components/cmp_enemy_ai.h"
#include "../components/cmp_enemy_turret.h"
#include "../components/cmp_hurt_player.h"
#include "../components/cmp_physics.h"
#include "../components/cmp_player_physics.h"
#include "../game.h"
#include "../components/cmp_weapon_system.h"
#include "../components/cmp_hp.h"
#include <LevelSystem.h>
#include <iostream>
#include <SFML/Audio/Music.hpp>
using namespace std;
using namespace sf;

static shared_ptr<Entity> player;

void Level2Scene::Load() {
  cout << "Scene 2 Load" << endl;
  ls::loadLevelFile("res/levels/level_2.txt", 40.0f);
  auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
  ls::setOffset(Vector2f(0, ho));
  // Create player
  {
    // *********************************
	player = makeEntity();
	player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	auto s = player->addComponent<ShapeComponent>();
	s->setShape<sf::RectangleShape>(Vector2f(20.f, 30.f));
	s->getShape().setFillColor(Color::Magenta);
	s->getShape().setOrigin(10.f, 15.f);
	player->addComponent<WeaponSystemComponent>();
	player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 30.f));
    // *********************************
    player->addTag("player");
    //player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 30.f));
	
  }

  // Create Enemy
  {
    auto enemy = makeEntity();
    enemy->setPosition(ls::getTilePosition(ls::findTiles(ls::ENEMY)[0]) +
                       Vector2f(0, 24));
    // *********************************
    // Add HurtComponent
	enemy->addComponent<HurtComponent>();
	enemy->addComponent<HPComponent>();
    // Add ShapeComponent, Red 16.f Circle
	auto sEnemy = enemy->addComponent<ShapeComponent>();
	sEnemy->setShape<sf::CircleShape>(16.0f);
	sEnemy->getShape().setFillColor(Color::Green);
	enemy->addTag("enemy");
    // Add EnemyAIComponent
	enemy->addComponent<EnemyAIComponent>();
    // *********************************
  }

  {
	  auto enemy2 = makeEntity();
	  enemy2->setPosition(ls::getTilePosition(ls::findTiles(ls::ENEMY)[0]) +
		  Vector2f(0, 24));
	  // *********************************
	  // Add HurtComponent
	  enemy2->addComponent<HurtComponent>();
	  enemy2->addComponent<HPComponent>();
	  // Add ShapeComponent, Red 16.f Circle
	  auto sEnemy2 = enemy2->addComponent<ShapeComponent>();
	  sEnemy2->setShape<sf::CircleShape>(16.0f);
	  sEnemy2->getShape().setFillColor(Color::Green);
	  enemy2->addTag("enemy");
	  // Add EnemyAIComponent
	  enemy2->addComponent<EnemyAIComponent>();
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
  cout << " Scene 2 Load Done" << endl;
  setLoaded(true);
}

void Level2Scene::UnLoad() {
  cout << "Scene 2 UnLoad" << endl;
  player.reset();
  ls::unload();
  Scene::UnLoad();
}

void Level2Scene::Update(const double& dt) {
  Scene::Update(dt);

  const auto pp = player->getPosition();
  if (ls::getTileAt(pp) == ls::END) {
    Engine::ChangeScene((Scene*)&level3);
  } else if (!player->isAlive()) {
    Engine::ChangeScene((Scene*)&level2);
  }
}

void Level2Scene::Render() {
  ls::render(Engine::GetWindow());
  Scene::Render();
}
