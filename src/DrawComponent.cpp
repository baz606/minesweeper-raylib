//
// Created by shehbaz on 12/12/2023.
//

#include "DrawComponent.h"
#include "Actor.h"

DrawComponent::DrawComponent(const std::string &name, Actor *owner, int drawOrder)
:Component(name, owner)
,mDrawOrder(drawOrder)
{
  mOwner->GetGame()->AddDraw(this);
  mPosX = mOwner->GetPosition().x;
  mPosY = mOwner->GetPosition().y;
  mIsShow = true;
}

DrawComponent::~DrawComponent()
{
  mOwner->GetGame()->RemoveDraw(this);
}

void DrawComponent::SetPosition(float posX, float posY)
{
  mPosX = posX;
  mPosY = posY;
}
