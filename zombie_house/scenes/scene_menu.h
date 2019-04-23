#pragma once

#include "engine.h"

class MenuScene : public Scene {
public:
  //MenuScene() = default;
  //~MenuScene() override = default;
  void UnLoad() override;
  void Render() override;
  void Load() override;

  void Update(const double& dt) override;
};
