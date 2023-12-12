//
// Created by shehbaz on 12/10/2023.
//

#include "MeshComponent.h"
#include "Cell.h"

MeshComponent::MeshComponent(Actor *owner, Color color, Color borderColor, float thickness, int drawOrder)
:Component(owner)
,mColor(color)
,mBorderColor(borderColor)
,mThickness(thickness)
,mDrawOrder(drawOrder)
{
  mOwner->GetGame()->AddMesh(this);
}


MeshComponent::~MeshComponent()
{
  mOwner->GetGame()->RemoveMesh(this);
}

void MeshComponent::Draw()
{
  DrawRectangleRec(mRectangle, mColor);
  DrawRectangleLinesEx(mRectangle, mThickness, mBorderColor);
}

void MeshComponent::SetRectangle(float x, float y, float width, float height)
{
  mRectangle = { x, y, width, height };
}
