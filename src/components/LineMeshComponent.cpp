//
// Created by shehbaz on 12/14/2023.
//

#include "LineMeshComponent.h"

LineMeshComponent::LineMeshComponent(const std::string &name, Actor *owner, int drawOrder)
:DrawComponent(name, owner, drawOrder)
{
  mIsShow = false;
  mThickness = 3.f;
  mColor = BLACK;
}

void LineMeshComponent::Draw()
{
  if (mIsShow)
  {
    for (auto iter_s = startPosVec.begin(), iter_e = endPosVec.begin();
          iter_s != startPosVec.end() && iter_e != endPosVec.end();
          ++iter_s, ++iter_e)
    {
      DrawLineEx((*iter_s), (*iter_e), mThickness, mColor);
    }
  }
}

void LineMeshComponent::SetLinePair(const Vector2& startPos, const Vector2& endPos)
{
  startPosVec.push_back(startPos);
  endPosVec.push_back(endPos);
}


