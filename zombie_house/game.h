
#pragma once

#include "scenes/scene_level1.h"
#include "scenes/scene_level2.h"
#include "scenes/scene_level3.h"
#include "scenes/scene_level4.h"
#include "scenes/scene_level5.h"
#include "scenes/scene_level6.h"
#include "scenes/scene_level7.h"
#include "scenes/scene_level8.h"
#include "scenes/scene_level9.h"
#include "scenes/scene_level10.h"
#include "scenes/scene_menu.h"
#include "scenes/scene_controls.h"
#include <map>
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <set>



extern MenuScene menu;
extern Level1Scene level1;
extern Level2Scene level2;
extern Level3Scene level3;
extern Level4Scene level4;
extern Level5Scene level5;
extern Level6Scene level6;
extern Level7Scene level7;
extern Level8Scene level8;
extern Level9Scene level9;
extern Level10Scene level10;
extern ControlScene controls;
extern struct MyKeys
{
	//InputType myInputType;
	sf::Event::EventType myEventType;
	sf::Keyboard::Key key_pressed;
	int joyButton;
	sf::Mouse::Button myMouseButton;
};

extern struct Enemies
{
	std::weak_ptr<Entity> en;
};

extern struct Ammo
{
	std::weak_ptr<Entity> am;
};
extern std::map<std::string, MyKeys> m_keys;
extern bool ctrl_change;
extern std::map<std::int8_t, Enemies> _enemies;
extern std::map<std::int8_t, Ammo> _ammo;
extern int zombieKillCount;
extern int ammoPickupCount;