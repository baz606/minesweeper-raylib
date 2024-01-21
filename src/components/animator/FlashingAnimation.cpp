//
// Created by shehbaz on 1/16/2024.
//

#include "FlashingAnimation.h"
#include "../DrawComponent.h"
#include "raylib.h"

FlashingAnimation::FlashingAnimation(Animator *animator, DrawComponent* drawComponent, float speed)
:Animation(animator, speed)
{
  mDrawComponent = drawComponent;
}

bool FlashingAnimation::Play(float deltaTime)
{
  mTime += deltaTime;
  if (mTime > (mSpeed / 2.f))
  {
    mDrawComponent->SetIsShow(!mDrawComponent->GetIsShow());
    mTime = 0.f;
  }
  return true;
}
