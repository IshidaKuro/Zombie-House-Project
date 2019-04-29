#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"
#include <SFML/Window/Keyboard.hpp>

using namespace std;

MenuScene menu;
Level1Scene level1;
Level2Scene level2;
Level3Scene level3;
Level4Scene level4;
Level5Scene level5;
Level6Scene level6;
Level7Scene level7;
Level8Scene level8;
Level9Scene level9;
Level10Scene level10;
ControlScene controls;


int main() {

  Engine::Start(1280, 720, "Zombie House",&menu);
}