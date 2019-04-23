#include "scene_level1.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_weapon_system.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include <list>
#include <SFML/Audio/Music.hpp>

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;


list<Entity> zombies;


int numberOfZombies = 3;

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
  }

  //create some zombies
  {
	  for (int i = 0; i < numberOfZombies; i++)
	  {
		  
	  }
  
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

  Music music;
  if (!music.openFromFile("res/sounds/background.wav"))
  {
	  cout << "Error loading music";
  }
  else
  {
	  music.play();
  }
  
  //Simulate long loading times
  //std::this_thread::sleep_for(std::chrono::milliseconds(3000));
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
    Engine::ChangeScene((Scene*)&level2);
  }

  Scene::Update(dt);
}

void Level1Scene::Render() {
  ls::render(Engine::GetWindow());
  Scene::Render();
}
