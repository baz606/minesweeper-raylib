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

  // Getters and Setters
  [[nodiscard]] const Vector2& GetPosition() const { return mPosition; }
  void SetPosition(const Vector2& pos) { mPosition = pos; }
  void SetPosition(float x, float y);
  [[nodiscard]] float GetScale() const { return mScale; }
  [[nodiscard]] float GetRotation() const { return mRotation; }
  void SetRotation(float rotation) { mRotation = rotation; }

  [[nodiscard]] State GetState() const { return mState; }
  void SetState(State state) { mState = state; }

  class Game* GetGame() { return mGame; }

  // Add/Remove components
  void AddComponent(class Component* component);
  void RemoveComponent(class Component* component);

private:
  State mState;

  // Transform
  Vector2 mPosition;
  float mScale;
  float mRotation;

  std::vector<class Component*> mComponents;
  class Game* mGame;
};
