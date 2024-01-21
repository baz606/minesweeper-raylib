//
// Created by shehbaz on 1/15/2024.
//

#include "Animation.h"
#include "Animator.h"

Animation::Animation(Animator* animator, float speed)
:mAnimator(animator)
,mSpeed(speed)
{
  mAnimator->AddAnimation(this);
}

Animation::~Animation()
{
  mAnimator->RemoveAnimation(this);
}
