#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <ecm.h>
#include "../game.h"
#include <map>

class ControlComponent : public Component {
protected:
	char left_move;
	char right_move;
	
	
public:
  void update(double dt) override;
  void render() override {}
  void setLeft();
  void setRight();
  explicit ControlComponent(Entity* p);
  ControlComponent() = delete;
};
