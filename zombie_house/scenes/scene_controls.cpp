#include "scene_controls.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Joystick.hpp>
#include <iostream>

using namespace std;
using namespace sf;

bool choose = true;
bool ctrl_change;
void ControlScene::Load() {
	choose = true;
  cout << "Menu Load \n";
  {
    auto txt = makeEntity();
    auto t = txt->addComponent<TextComponent>(

        "Platformer Control Mapping\nPress Enter at any time to Return to Menu\nPress Left to change Left\nRight to change Right\nSpace to change shoot\n");

  }
  setLoaded(true);
}

void ControlScene::UnLoad()
{
	Scene::UnLoad();
}

void ControlScene::Update(const double& dt) {
  // cout << "Menu Update "<<dt<<"\n";

	Event choice_event;
	Event in_event;
	MyKeys key;
	while (choose == true)
	{
		//cout << "Choosing..";

		while (Engine::GetWindow().pollEvent(choice_event))
		{
			if (choice_event.type == sf::Event::KeyReleased)
			{
				if (choice_event.key.code == sf::Keyboard::Enter)
				{
					//cout << "Up Pressed";
					choose = false;
					ctrl_change = true;
					Engine::ChangeScene(&menu);
				}
			}
			if (choice_event.type == sf::Event::JoystickButtonPressed)
			{
				if (choice_event.joystickButton.button == Joystick::isButtonPressed(0, 14))
				{
					if (Engine::GetWindow().waitEvent(in_event))
					{
						key.myEventType == Event::JoystickButtonPressed;
						key.key_pressed == in_event.joystickButton.button;
						m_keys["Joy_Left"] = key;
					}
				}
				if (choice_event.joystickButton.button == Joystick::isButtonPressed(0, 15))
				{
					if (Engine::GetWindow().waitEvent(in_event))
					{
						key.myEventType == Event::JoystickButtonPressed;
						key.key_pressed == in_event.joystickButton.button;
						m_keys["Joy_Right"] = key;
					}
				}
				if (choice_event.joystickButton.button == Joystick::isButtonPressed(0, 14))
				{
					if (Engine::GetWindow().waitEvent(in_event))
					{
						key.myEventType == Event::JoystickButtonPressed;
						key.key_pressed == in_event.joystickButton.button;
						m_keys["Joy_Shoot"] = key;
					}
				}
			}
			if (choice_event.type == sf::Event::KeyReleased)
			{
				if (choice_event.key.code == sf::Keyboard::Left)
				{
					cout << "Left pressed";
					if (Engine::GetWindow().waitEvent(in_event))
					{
						if (in_event.type == sf::Event::KeyPressed)
						{
							key.myEventType = Event::KeyPressed;
							key.key_pressed = in_event.key.code;
							m_keys["Left"] = key;
							cout << "CHOSE NEW KEY FOR LEFT";
						}
					}
				}
				if (choice_event.key.code == sf::Keyboard::Right)
				{
					cout << "Right pressed";
					if (Engine::GetWindow().waitEvent(in_event))
					{
						if (in_event.type == sf::Event::KeyPressed)
						{
							key.myEventType = Event::KeyPressed;
							key.key_pressed = in_event.key.code;
							m_keys["Right"] = key;
							cout << "CHOSE NEW KEY FOR RIGHT";
						}
					}
				}
				if (choice_event.key.code == sf::Keyboard::Space)
				{
					cout << "Space pressed";
					if (Engine::GetWindow().waitEvent(in_event))
					{
						if (in_event.type == sf::Event::KeyPressed)
						{
							key.myEventType = Event::KeyPressed;
							key.key_pressed = in_event.key.code;
							m_keys["Shoot"] = key;
							cout << "CHOSE NEW KEY FOR SPACE";
						}
					}
				}
			}
		}
	}
	
	cout << "Not choosing";
	Scene::Update(dt);
	
}

void ControlScene::Render()
{
	Scene::Render();
}
