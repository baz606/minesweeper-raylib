//
// Created by shehbaz on 1/20/2024.
//

#pragma once

#include "Actor.h"


class Logo : public Actor
{
public:
  Logo(Game* game, Game::GameState gameState);

  void Init();
  void UpdateActor(float deltaTime) override;
};
