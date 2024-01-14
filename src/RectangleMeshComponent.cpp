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
    mRectangle = { (float)mOwner->GetPosition().x,
                   (float)mOwner->GetPosition().y,
                   (float)mWidth * mOwner->GetScale(),
                   (float)mHeight * mOwner->GetScale()};

    DrawRectanglePro(mRectangle,
                     { mWidth / 2.f, mHeight / 2.f },
                     mOwner->GetRotation(),
                     mColor);
    DrawRectangleLinesEx(
            { mRectangle.x - (mWidth / 2.f), mRectangle.y - (mHeight / 2.f),
              mRectangle.width, mRectangle.height },
              mThickness, mBorderColor
            );
  }
}
