//
// Created by shehbaz on 12/10/2023.
//

#pragma once

#include "Component.h"
#include "Actor.h"

class MeshComponent : public Component
{
public:
  MeshComponent(Actor* owner, int drawOrder = 100);
  ~MeshComponent();

  void Draw();

  void SetRectangle(float x, float y, float width, float height);
  [[nodiscard]] const Rectangle& GetRectangle() const { return mRectangle; }
  void SetColor(Color color) { mColor = color; }
  [[nodiscard]] const Color& GetColor() const { return mColor; }
  int GetDrawOrder() const { return mDrawOrder;}

private:
  // Rectangle and color used to draw the actor
  Rectangle mRectangle;
  Color mColor;
  int mDrawOrder;
};
