//
// Created by shehbaz on 12/10/2023.
//

#include "MeshComponent.h"

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
  DrawRectangleRec(mRectangle, mColor);
}

void MeshComponent::SetRectangle(float x, float y, float width, float height)
{
  mRectangle = { x, y, width, height };
}
