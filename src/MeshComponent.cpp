//
// Created by shehbaz on 12/10/2023.
//

#include "MeshComponent.h"
#include "Cell.h"

MeshComponent::MeshComponent(const std::string& name, Actor *owner, int drawOrder)
: DrawComponent(name, owner, drawOrder)
{
  mThickness = 0.0f;
}

void MeshComponent::Draw()
{
  mPosX = mOwner->GetPosition().x - ((float)mWidth / 2);
  mPosY = mOwner->GetPosition().y - ((float)mHeight / 2);

  mRectangle = { (float)mPosX,
                 (float)mPosY,
                 (float)mWidth * mOwner->GetScale(),
                 (float)mHeight * mOwner->GetScale()};

  DrawRectangleRec(mRectangle, mColor);
  DrawRectangleLinesEx(mRectangle, mThickness, mBorderColor);
}
