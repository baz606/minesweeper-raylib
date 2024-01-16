//
// Created by shehbaz on 1/15/2024.
//

#include "TransformAnimation.h"
#include "Animator.h"
#include "raymath.h"

TransformAnimation::TransformAnimation(Animator *animator, float speed)
:Animation(animator, speed)
{
  mFinalPosition = animator->GetOwner()->GetPosition();
  mFinalRotation = animator->GetOwner()->GetRotation();
  mFinalScale = animator->GetOwner()->GetScale();
}

bool TransformAnimation::Play()
{
  return UpdatePosition() || UpdateRotation() || UpdateScale();
}

bool TransformAnimation::UpdateRotation()
{
  float rotation = mAnimator->GetOwner()->GetRotation();
  if (!FloatEquals(rotation, mFinalRotation))
  {
    if (mFinalRotation > rotation)
    {
      rotation += (mSpeed * GetFrameTime());
    }
    else
    {
      rotation -= (mSpeed * GetFrameTime());
    }
    mAnimator->GetOwner()->SetRotation(rotation);
    return true;
  }
  return false;
}

bool TransformAnimation::UpdatePosition()
{
  Vector2 position = mAnimator->GetOwner()->GetPosition();
  if (!Vector2Equals(position, mFinalPosition))
  {
    if (!FloatEquals(position.x, mFinalPosition.x))
    {
      if (mFinalPosition.x > position.x)
      {
        position.x += (mSpeed * GetFrameTime());
      }
      else
      {
        position.x -= (mSpeed * GetFrameTime());
      }
    }
    if (!FloatEquals(position.y, mFinalPosition.y))
    {
      if (mFinalPosition.y > position.y)
      {
        position.y += (mSpeed * GetFrameTime());
      }
      else
      {
        position.y -= (mSpeed * GetFrameTime());
      }
    }
    mAnimator->GetOwner()->SetPosition(position);
    return true;
  }
  return false;
}

bool TransformAnimation::UpdateScale()
{
  float scale = mAnimator->GetOwner()->GetScale();
  if (!FloatEquals(scale, mFinalScale))
  {
    if (mFinalScale > scale)
    {
      scale += (mSpeed * GetFrameTime());
    }
    else
    {
      scale -= (mSpeed * GetFrameTime());
    }
    mAnimator->GetOwner()->SetScale(scale);
    return true;
  }
  return false;
}
