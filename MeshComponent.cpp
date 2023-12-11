//
// Created by shehbaz on 12/10/2023.
//

#include "MeshComponent.h"
#include "Cell.h"

MeshComponent::MeshComponent(Actor *owner, int drawOrder)
:Component(owner, drawOrder)
{
  mOwner->GetGame()->AddMesh(this);
}

MeshComponent::~MeshComponent()
{
  mOwner->GetGame()->RemoveMesh(this);
}

void MeshComponent::Draw()
{
  CellType cellType = reinterpret_cast<Cell*>(mOwner)->GetCellType();
  switch (cellType)
  {
    case UNEXPOSE:
      DrawRectangleRec(mRectangle, mColor);
      DrawRectangleLinesEx(mRectangle, 3.0f, mBorderColor);
      break;

    default:
      DrawRectangleRec(mRectangle, mColor);
      DrawRectangleLinesEx(mRectangle, 3.0f, mBorderColor);
  }
}

void MeshComponent::SetRectangle(float x, float y, float width, float height)
{
  mRectangle = { x, y, width, height };
}
