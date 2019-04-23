
#pragma once

#include "scenes/scene_level1.h"
#include "scenes/scene_level2.h"
#include "scenes/scene_level3.h"
#include "scenes/scene_menu.h"
#include "scenes/scene_controls.h"
#include <map>
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <array>



extern MenuScene menu;
extern Level1Scene level1;
extern Level2Scene level2;
extern Level3Scene level3;
extern ControlScene controls;
extern struct MyKeys
{
	//InputType myInputType;
	sf::Event::EventType myEventType;
	sf::Keyboard::Key key_pressed;
	sf::Mouse::Button myMouseButton;
};
extern std::map<std::string, MyKeys> m_keys;
extern bool ctrl_change;
extern std::weak_ptr<Entity> _enemy[10];