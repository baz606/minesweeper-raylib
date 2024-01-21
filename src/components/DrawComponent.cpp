//
// Created by shehbaz on 12/12/2023.
//

#include "DrawComponent.h"
#include "../actors/Actor.h"

DrawComponent::DrawComponent(const std::string &name, Actor *owner, int drawOrder)
:Component(name, owner)
,mDrawOrder(drawOrder)
{
  mOwner->GetGame()->AddDraw(this);
  mIsShow = true;
}

DrawComponent::~DrawComponent()
{
  mOwner->GetGame()->RemoveDraw(this);
}
