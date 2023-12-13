//
// Created by shehbaz on 12/10/2023.
//

#include "MeshComponent.h"
#include "Cell.h"

MeshComponent::MeshComponent(const std::string& name, Actor *owner, int drawOrder)
:Component(owner, name)
,mDrawOrder(drawOrder)
{
  mOwner->GetGame()->AddMesh(this);
  mThickness = 0.0f;
}


MeshComponent::~MeshComponent()
{
  mOwner->GetGame()->RemoveMesh(this);
}

void MeshComponent::Draw()
{
  mRectangle = { mOwner->GetPosition().x - ((float)mWidth / 2),
                 mOwner->GetPosition().y - ((float)mHeight / 2),
                 (float)mWidth * mOwner->GetScale(),
                 (float)mHeight * mOwner->GetScale()};

  DrawRectangleRec(mRectangle, mColor);
  DrawRectangleLinesEx(mRectangle, mThickness, mBorderColor);
}
