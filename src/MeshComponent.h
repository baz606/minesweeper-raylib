//
// Created by shehbaz on 12/10/2023.
//

#pragma once

#include "Component.h"
#include "Actor.h"
#include "DrawComponent.h"

class MeshComponent : public DrawComponent
{
public:
  MeshComponent(const std::string& name, Actor* owner, int drawOrder = 100);

  void Draw() override;

  // Setters/Getters
  void SetColor(Color color) { mColor = color; }
  void SetBorderColor(Color borderColor) { mBorderColor = borderColor; }
  void SetBorderThickness(float thickness) { mThickness = thickness; }
  [[nodiscard]] const Color& GetColor() const { return mColor; }
  int GetDrawOrder() const { return mDrawOrder;}
  void SetHeight(int height) { mHeight = height; }
  [[nodiscard]] int GetHeight() const { return mHeight; }
  void SetWidth(int width) { mWidth = width; }
  [[nodiscard]] int GetWidth() const { return mWidth; }

private:
  // Rectangle and color used to draw the actor
  Rectangle mRectangle;
  int mWidth, mHeight;
  Color mColor, mBorderColor;
  float mThickness;
};
