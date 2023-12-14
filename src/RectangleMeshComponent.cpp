//
// Created by shehbaz on 12/10/2023.
//

#include "RectangleMeshComponent.h"
#include "Cell.h"

RectangleMeshComponent::RectangleMeshComponent(const std::string& name, Actor *owner, int drawOrder)
:DrawComponent(name, owner, drawOrder)
{
  mThickness = 0.0f;
}

void RectangleMeshComponent::Draw()
{
  if (mIsShow)
  {
    mRectangle = { (float)mPosX - ((float)mWidth / 2),
                   (float)mPosY - ((float)mHeight / 2),
                   (float)mWidth * mOwner->GetScale(),
                   (float)mHeight * mOwner->GetScale()};

    DrawRectangleRec(mRectangle, mColor);
    DrawRectangleLinesEx(mRectangle, mThickness, mBorderColor);
  }
}
