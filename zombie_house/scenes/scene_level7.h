#pragma once

#include "engine.h"

class Level7Scene : public Scene {
public:
  void Load() override;

  void UnLoad() override;

  void Update(const double& dt) override;

  void Render() override;
};