//
// Created by shehbaz on 1/18/2024.
//

#pragma once

#include "Component.h"
#include "raylib.h"

class BoxCollider : public Component
{
public:
  BoxCollider(const std::string& name, Actor *owner, int updateOrder = 100);
  ~BoxCollider() override;

  // Setters/Getters
  void SetCollider(float x, float y, float width, float height);
  [[nodiscard]] const Rectangle* GetRectangle() const { return mCollider; }

  void Update(float deltaTime) override;
  bool OnMouseHover();

private:
  // The x,y position of this collider is top left of the box/rectangle
  Rectangle* mCollider;
};
