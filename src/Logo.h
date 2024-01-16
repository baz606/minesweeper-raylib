//
// Created by shehbaz on 1/14/2024.
//

#pragma once

#include "Actor.h"


class Logo : public Actor
{
public:
  Logo(Game* game, Game::GameState gameState);
  void Init();
};
