//
// Created by shehbaz on 1/16/2024.
//

#pragma once

#include "Actor.h"

class Caption : public Actor
{
public:
  Caption(Game* game, Game::GameState gameState);
  void Init();
};
