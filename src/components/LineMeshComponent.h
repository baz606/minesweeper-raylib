//
// Created by shehbaz on 12/14/2023.
//

#pragma once

#include "DrawComponent.h"
#include "../actors/Actor.h"

class LineMeshComponent : public DrawComponent
{
public:
  LineMeshComponent(const std::string& name, Actor* owner, int drawOrder = 100);

  void Draw() override;

  void SetLinePair(const Vector2& startPos, const Vector2& endPos);
  void SetThickness(float thickness) { mThickness = thickness; }
  void SetColor (Color color) { mColor = color; }

private:
  std::vector<Vector2> startPosVec;
  std::vector<Vector2> endPosVec;
  float mThickness;
  Color mColor;
};
