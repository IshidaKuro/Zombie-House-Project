#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../components/cmp_physics.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_pickup_ammo.h"
#include "system_resources.h"
#include "../game.h"
#include "../components/cmp_persistence.h"
#include "../components/cmp_weapon_system.h"
#include "../components/cmp_hp.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Joystick.hpp>
#include <iostream>
#include <system_renderer.h>
#include <LevelSystem.h>


using namespace std;
using namespace sf;
#define GAMEX 1280
#define GAMEY 720
static shared_ptr<Entity> player;
std::map<std::string, MyKeys> m_keys;
std::map<std::int8_t, Enemies> _enemies;
std::map<std::int8_t, Ammo> _ammo;
int zombieKillCount;
int ammoPickupCount;
string out_level;

sf::FloatRect CalculateViewport(const sf::Vector2u& screensize,
	const sf::Vector2u& gamesize) {

	const Vector2f screensf(screensize.x, screensize.y);
	const Vector2f gamesf(gamesize.x, gamesize.y);
	const float gameAspect = gamesf.x / gamesf.y;
	const float screenAspect = screensf.x / screensf.y;
	float scaledWidth;  // final size.x of game viewport in piels
	float scaledHeight; //final size.y of game viewport in piels
	bool scaleSide = false; // false = scale to screen.x, true = screen.y

	//Work out which way to scale
	if (gamesize.x > gamesize.y) { // game is wider than tall
	  // Can we use full width?
		if (screensf.y < (screensf.x / gameAspect)) {
			//no, not high enough to fit game height
			scaleSide = true;
		}
		else {
			//Yes, use all width available
			scaleSide = false;
		}
	}
	else { // Game is Square or Taller than Wide
   // Can we use full height?
		if (screensf.x < (screensf.y * gameAspect)) {
			// No, screensize not wide enough to fit game width
			scaleSide = false;
		}
		else {
			// Yes, use all height available
			scaleSide = true;
		}
	}

	if (scaleSide) { // use max screen height
		scaledHeight = screensf.y;
		scaledWidth = floor(scaledHeight * gameAspect);
	}
	else { //use max screen width
		scaledWidth = screensf.x;
		scaledHeight = floor(scaledWidth / gameAspect);
	}

	//calculate as percent of screen
	const float widthPercent = (scaledWidth / screensf.x);
	const float heightPercent = (scaledHeight / screensf.y);

	return sf::FloatRect(0, 0, widthPercent, heightPercent);
}

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

  //loads last entered level
  string prev_level = l->LoadFile("ZombieHouseSaveFile.txt");
  if (prev_level.size() > 0)
  {
	   out_level = prev_level[0];
  }

  {
    auto txt = makeEntity();
    auto t = txt->addComponent<TextComponent>(
		
        "Interact (E/BButton) with the door to start/continue\nPress F1 to enter windowed from fullscreen menu\nInteract with blue square to remap controls\nPress S during a level to save and menu");
  }

  //set initial default controls if the user hasn't changed them this session
  if (ctrl_change == false)
  {
	  MyKeys key;
	  key.key_pressed = Keyboard::Left;
	  m_keys["Left"] = key;
	  key.key_pressed = Keyboard::Right;
	  m_keys["Right"] = key;
	  key.key_pressed = Keyboard::Space;
	  m_keys["Shoot"] = key;
	  key.key_pressed = Keyboard::E;
	  m_keys["Interact"] = key;
	  key.key_pressed = Keyboard::R;
	  m_keys["Reload"] = key;
	  key.key_pressed = Keyboard::Num1;
	  m_keys["Switch_Pistol"] = key;
	  key.key_pressed = Keyboard::Num2;
	  m_keys["Switch_Smg"] = key;
	  key.key_pressed = Keyboard::Num3;
	  m_keys["Switch_Shotgun"] = key;
	  key.key_pressed = Keyboard::Up;
	  m_keys["Jump"] = key;

	  key.joyButton = -Joystick::PovX;
	  m_keys["Joy_Left"] = key;
	  key.joyButton = Joystick::PovX;
	  m_keys["Joy_Right"] = key;
	  key.joyButton = 0;
	  m_keys["Joy_Shoot"] = key;
	  key.joyButton = 1;
	  m_keys["Joy_Interact"] = key;
	  key.joyButton = 2;
	  m_keys["Joy_Reload"] = key;
	  key.joyButton = 3;
	  m_keys["Joy_Switch_Pistol"] = key;
	  key.joyButton = 4;
	  m_keys["Joy_Switch_Smg"] = key;
	  key.joyButton = 5;
	  m_keys["Joy_Switch_Shotgun"] = key;
	  key.joyButton = Joystick::PovY;
	  m_keys["Joy_Jump"] = key;

  }

  cout << " Menu Scene Load" << endl;
  ls::loadLevelFile("res/levels/menu.txt", 40.0f);

  auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
  ls::setOffset(Vector2f(0, ho));

  // Create player
  {
	  player = makeEntity();
	  player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	 
	  shared_ptr<Texture> spriteSheet;
	
	  spriteSheet = Resources::get<Texture>("player.png");

	  auto pSprite = player->addComponent<SpriteComponent>();
	  pSprite->setTexure(spriteSheet);
	  pSprite->getSprite().scale(2.0f, 2.0f);
	  pSprite->getSprite().setOrigin(10.f, 15.f);

	  player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 30.f));
	  player->addComponent<WeaponSystemComponent>();
	  auto a = player->addComponent<PickupAmmoComponent>();
	  a->setAmmo("pistol", 8);
	  a->setAmmo("smg", 20);
	  a->setAmmo("shotgun", 4);

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

  auto door = makeEntity();
  door->setPosition(ls::getTilePosition(ls::findTiles(ls::END)[0]));

  shared_ptr<Texture> spriteSheet;

  spriteSheet = Resources::get<Texture>("door.png");

  auto dSprite = door->addComponent<SpriteComponent>();
  dSprite->setTexure(spriteSheet);
  dSprite->getSprite().scale(2.0f, 2.0f);
  dSprite->getSprite().setOrigin(0.f, -10.f);

  setLoaded(true);
}

void MenuScene::Update(const double& dt) {
  // cout << "Menu Update "<<dt<<"\n";

	if (ls::getTileAt(player->getPosition()) == ls::END && (Keyboard::isKeyPressed(m_keys["Interact"].key_pressed) || Joystick::isButtonPressed(0, m_keys["Joy_Interact"].joyButton))) {
		if (out_level != "")
		{
			if (out_level == "1")
			{
				Engine::ChangeScene(&level1);
			}
			else if (out_level == "2")
			{
				Engine::ChangeScene(&level2);
			}
			else if(out_level == "3")
			{
				Engine::ChangeScene(&level3);
			}	
			else if (out_level == "4")
			{
				Engine::ChangeScene(&level4);
			}
			else if (out_level == "5")
			{
				Engine::ChangeScene(&level5);
			}
			else if (out_level == "6")
			{
				Engine::ChangeScene(&level6);
			}
			else if (out_level == "7")
			{
				Engine::ChangeScene(&level7);
			}
			else if (out_level == "8")
			{
				Engine::ChangeScene(&level8);
			}
			else if (out_level == "9")
			{
				Engine::ChangeScene(&level9);
			}
			else if (out_level == "10")
			{
				Engine::ChangeScene(&level10);
			}
		}
		else
		{
			Engine::ChangeScene((Scene*)&level1);
		}
	}
	else if (ls::getTileAt(player->getPosition()) == ls::WAYPOINT && (Keyboard::isKeyPressed(m_keys["Interact"].key_pressed) || Joystick::isButtonPressed(0, m_keys["Joy_Interact"].joyButton)))
	{
		Engine::ChangeScene((Scene*)(&controls));
	}

	if (Keyboard::isKeyPressed(Keyboard::F1))
	{
		const sf::Vector2u screensize(1280,720);
		const sf::Vector2u gamesize(GAMEX, GAMEY);
		//set View as normal
		Engine::GetWindow().setSize(screensize);
		sf::FloatRect visibleArea(0.f, 0.f, gamesize.x, gamesize.y);
		auto v = sf::View(visibleArea);
		// figure out how to scale and maintain aspect;
		auto viewport = CalculateViewport(screensize, gamesize);
		//Optionally Center it
		bool centered = true;
		if (centered) {
			viewport.left = (1.0 - viewport.width) * 0.5;
			viewport.top = (1.0 - viewport.height) * 0.5;
		}
		//set!
		v.setViewport(viewport);
		Engine::GetWindow().setView(v);
	}
  Scene::Update(dt);
}

void MenuScene::UnLoad()
{
	cout << "Menu Scene Unload" << endl;
	player.reset();
	ls::unload();
	Scene::UnLoad();
}

void MenuScene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}