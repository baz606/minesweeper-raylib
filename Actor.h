//
// Created by shehbaz on 12/10/2023.
//

#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "Game.h"
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

  // Add/Remove from components hash map
  void AddComponentToMap(std::string& name, class Component* component);
  void RemoveComponentFromMap(std::string& name);

  // Get component using the mComponentsMap
  Component* GetComponent(const std::string& name);

private:
  State mState;

  // Transform
  Vector2 mPosition;
  float mScale;
  float mRotation;

  std::vector<class Component*> mComponents;
  std::unordered_map<std::string, class Component*> mComponentsMap;
  class Game* mGame;
};
