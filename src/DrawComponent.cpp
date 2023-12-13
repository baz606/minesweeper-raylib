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
}

DrawComponent::~DrawComponent()
{
  printf("DrawComponent destructor called...\n");
  mOwner->GetGame()->RemoveDraw(this);
}

void DrawComponent::SetPosition(int posX, int posY)
{
  mPosX = posX;
  mPosY = posY;
}