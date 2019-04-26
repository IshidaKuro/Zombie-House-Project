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

        "Platformer Control Mapping\n"
		"Press button then press new button\nDo not press enter before choosing a new button\nPlease don't choose the same key as a change\n-change it then switch back"
		"\nPress Enter at any time to Return to Menu\n\nPress Left to change Left\nRight to change Right\nSpace/A Button to change shoot\nR Key\X Button to change Reload\n"
		"Up Arrow to change Jump\n1 to change pistol switch, 2 to change SMG switch\nor 3 to change shotgun switch\n"
		"RB to change shotgun switch, LB to change SMG switch\nor Y to change pistol switch\n");

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
			if (choice_event.type == sf::Event::JoystickButtonReleased)
			{
				if (choice_event.joystickButton.button == 0)
				{
					cout << "A";
					if (Engine::GetWindow().waitEvent(in_event))
					{
						
						key.myEventType = Event::JoystickButtonPressed;
						key.joyButton  = in_event.joystickButton.button;
						m_keys["Joy_Shoot"] = key;
						cout << "Choosing A";
					}
				}
				if (choice_event.joystickButton.button == 2)
				{
					cout << "B";
					if (Engine::GetWindow().waitEvent(in_event))
					{
				
						key.myEventType = Event::JoystickButtonPressed;
						key.joyButton = in_event.joystickButton.button;
						m_keys["Joy_Reload"] = key;
					}
				}
				if (choice_event.joystickButton.button == 3)
				{
					cout << "Y";
					if (Engine::GetWindow().waitEvent(in_event))
					{

						key.myEventType = Event::JoystickButtonPressed;
						key.joyButton = in_event.joystickButton.button;
						m_keys["Joy_Switch_Pistol"] = key;
					}
				}
				if (choice_event.joystickButton.button == 4)
				{
					//cout << "SMGGGGG";
					if (Engine::GetWindow().waitEvent(in_event))
					{

						key.myEventType = Event::JoystickButtonPressed;
						key.joyButton = in_event.joystickButton.button;
						m_keys["Joy_Switch_Smg"] = key;
					}
				}
				if (choice_event.joystickButton.button == 5)
				{
					cout << "Y";
					if (Engine::GetWindow().waitEvent(in_event))
					{

						key.myEventType = Event::JoystickButtonPressed;
						key.joyButton = in_event.joystickButton.button;
						m_keys["Joy_Switch_Shotgun"] = key;
					}
				}
				if (choice_event.joystickButton.button == 1)
				{
					//cout << "Y";
					if (Engine::GetWindow().waitEvent(in_event))
					{
						key.myEventType = Event::JoystickButtonPressed;
						key.joyButton = in_event.joystickButton.button;
						m_keys["Joy_Interact"] = key;
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
							//cout << "CHOSE NEW KEY FOR LEFT";
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
							//cout << "CHOSE NEW KEY FOR RIGHT";
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
							//cout << "CHOSE NEW KEY FOR SPACE";
						}
					}
				}
				if (choice_event.key.code == sf::Keyboard::E)
				{
					//cout << "E pressed";
					if (Engine::GetWindow().waitEvent(in_event))
					{
						if (in_event.type == sf::Event::KeyPressed)
						{
							key.myEventType = Event::KeyPressed;
							key.key_pressed = in_event.key.code;
							m_keys["Interact"] = key;
							//cout << "CHOSE E";
							//cout << "CHOSE NEW KEY FOR RIGHT";
						}
					}
				}
				if (choice_event.key.code == sf::Keyboard::R)
				{
					//cout << "Space pressed";
					if (Engine::GetWindow().waitEvent(in_event))
					{
						if (in_event.type == sf::Event::KeyPressed)
						{
							key.myEventType = Event::KeyPressed;
							key.key_pressed = in_event.key.code;
							m_keys["Reload"] = key;
							//cout << "CHOSE NEW KEY FOR SPACE";
						}
					}
				}
				if (choice_event.key.code == sf::Keyboard::Num1)
				{
					//cout << "Space pressed";
					if (Engine::GetWindow().waitEvent(in_event))
					{
						if (in_event.type == sf::Event::KeyPressed)
						{
							key.myEventType = Event::KeyPressed;
							key.key_pressed = in_event.key.code;
							m_keys["Switch_Pistol"] = key;
							//cout << "CHOSE NEW KEY FOR SPACE";
						}
					}
				}
				if (choice_event.key.code == sf::Keyboard::Num2)
				{
					//cout << "Space pressed";
					if (Engine::GetWindow().waitEvent(in_event))
					{
						if (in_event.type == sf::Event::KeyPressed)
						{
							key.myEventType = Event::KeyPressed;
							key.key_pressed = in_event.key.code;
							m_keys["Switch_Smg"] = key;
							//cout << "CHOSE NEW KEY FOR SPACE";
						}
					}
				}
				if (choice_event.key.code == sf::Keyboard::Num3)
				{
					//cout << "Space pressed";
					if (Engine::GetWindow().waitEvent(in_event))
					{
						if (in_event.type == sf::Event::KeyPressed)
						{
							key.myEventType = Event::KeyPressed;
							key.key_pressed = in_event.key.code;
							m_keys["Switch_Shotgun"] = key;
							//cout << "CHOSE NEW KEY FOR SPACE";
						}
					}
				}
				if (choice_event.key.code == sf::Keyboard::Up)
				{
					//cout << "Space pressed";
					if (Engine::GetWindow().waitEvent(in_event))
					{
						if (in_event.type == sf::Event::KeyPressed)
						{
							key.myEventType = Event::KeyPressed;
							key.key_pressed = in_event.key.code;
							m_keys["Jump"] = key;
							//cout << "CHOSE NEW KEY FOR SPACE";
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
