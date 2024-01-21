//
// Created by shehbaz on 1/18/2024.
//

#pragma once

#include "Actor.h"

class BackButton : public Actor
{
public:
  BackButton(class Game* game, Game::GameState gameState);
  ~BackButton() override;

  void UpdateActor(float deltaTime) override;

  // Setters/Getters
  void SetOnHoverTexture(const Texture2D& onHoverTexture) { mOnHoverTexture = onHoverTexture; }
  void SetOffHoverTexture(const Texture2D& offHoverTexture) { mOffHoverTexture = offHoverTexture; }

private:
  Texture2D mOnHoverTexture, mOffHoverTexture;
};
