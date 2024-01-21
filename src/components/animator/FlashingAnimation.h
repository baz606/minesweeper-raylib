//
// Created by shehbaz on 1/16/2024.
//

#pragma once

#include "Animation.h"

// FLashing Animation flashes the draw component of an actor
class FlashingAnimation : public Animation
{
public:
  FlashingAnimation(Animator* animator, class DrawComponent* drawComponent, float speed);

  bool Play(float deltaTime) override;

private:
  float mTime;
  class DrawComponent* mDrawComponent;
};
