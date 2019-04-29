#pragma once

#include "cmp_actor_movement.h"

class EnemyAIComponent : public ActorMovementComponent {
protected:
  sf::Vector2f _direction;
  std::weak_ptr<Entity> _player;

public:
  void update(double dt) override;

  explicit EnemyAIComponent(Entity* p);

  EnemyAIComponent() = delete;
};
