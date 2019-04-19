#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

void MenuScene::Load() {
  cout << "Menu Load \n";
  {
    auto txt = makeEntity();
    auto t = txt->addComponent<TextComponent>(

        "Platformer\nPress Space to Start\nPress F1 to enter fullscreen\nPress C to remap controls");

  }
  setLoaded(true);
}

void MenuScene::Update(const double& dt) {
  // cout << "Menu Update "<<dt<<"\n";

  if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
    Engine::ChangeScene(&level2);
  }
  if (sf::Keyboard::isKeyPressed(Keyboard::C))
  {
	  Engine::ChangeScene(&controls);
  }

  Scene::Update(dt);
}
