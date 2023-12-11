//
// Created by shehbaz on 12/10/2023.
//

#pragma once

#include <vector>

#include "raylib.h"

class Actor
{
public:
  enum State
  {
    EActive,
    EPaused,
    EDead
  };

  Actor(class Game* game);
  virtual ~Actor();

  void Update(float deltaTime);
  void UpdateComponents(float deltaTime);
  virtual void UpdateActor(float deltaTime);

private:
  State mState;

  // Transform
  Vector2 mPosition;
  float mScale;
  float mRotation;

  std::vector<class Component*> mComponents;
  class Game* game;
};
