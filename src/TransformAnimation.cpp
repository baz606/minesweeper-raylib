//
// Created by shehbaz on 1/15/2024.
//

#include "TransformAnimation.h"
#include "Animator.h"
#include "raymath.h"

TransformAnimation::TransformAnimation(Animator *animator, float speed)
:Animation(animator, speed)
{
  mFinalPosition = nullptr;
  mFinalRotation = nullptr;
  mFinalScale = nullptr;
}

TransformAnimation::~TransformAnimation()
{
  // Deallocate memory
  delete mFinalPosition;
  delete mFinalRotation;
  delete mFinalScale;
}

bool TransformAnimation::Play(float deltaTime)
{
  bool isPlay = false;
  if (UpdatePosition(deltaTime))
  {
    isPlay = true;
  }
  if (UpdateRotation(deltaTime))
  {
    isPlay = true;
  }
  if (UpdateScale(deltaTime))
  {
    isPlay = true;
  }
  return isPlay;
}

bool TransformAnimation::UpdateRotation(float deltaTime)
{
  if (mFinalRotation)
  {
    float rotation = mAnimator->GetOwner()->GetRotation();
    float finalRotation = (*mFinalRotation);
    if (!FloatEquals(rotation, finalRotation))
    {
      if (finalRotation > rotation)
      {
        rotation += (mSpeed * deltaTime);
        if (rotation > finalRotation)
        {
          rotation = finalRotation;
        }
      }
      else
      {
        rotation -= (mSpeed * deltaTime);
        if (rotation < finalRotation)
        {
          rotation = finalRotation;
        }
      }
      mAnimator->GetOwner()->SetRotation(rotation);
      return true;
    }
  }

  return false;
}

bool TransformAnimation::UpdatePosition(float deltaTime)
{
  if (mFinalPosition)
  {
    Vector2 position = mAnimator->GetOwner()->GetPosition();
    Vector2 finalPosition = (*mFinalPosition);
    if (!Vector2Equals(position, finalPosition))
    {
      if (!FloatEquals(position.x, finalPosition.x))
      {
        if (finalPosition.x > position.x)
        {
          position.x += (mSpeed * deltaTime);
          if (position.x > finalPosition.x)
          {
            position.x = finalPosition.x;
          }
        }
        else
        {
          position.x -= (mSpeed * deltaTime);
          if (position.x < finalPosition.x)
          {
            position.x = finalPosition.x;
          }
        }
      }
      if (!FloatEquals(position.y, finalPosition.y))
      {
        if (finalPosition.y > position.y)
        {
          position.y += (mSpeed * deltaTime);
          if (position.y > finalPosition.y)
          {
            position.y = finalPosition.y;
          }
        }
        else
        {
          position.y -= (mSpeed * deltaTime);
          if (position.y < finalPosition.y)
          {
            position.y = finalPosition.y;
          }
        }
      }
      mAnimator->GetOwner()->SetPosition(position);
      return true;
    }
  }

  return false;
}

bool TransformAnimation::UpdateScale(float deltaTime)
{
  if (mFinalScale)
  {
    float scale = mAnimator->GetOwner()->GetScale();
    float finalScale = (*mFinalScale);
    if (!FloatEquals(scale, finalScale))
    {
      if (finalScale > scale)
      {
        scale += (mSpeed * deltaTime);
        if (scale > finalScale)
        {
          scale = finalScale;
        }
      }
      else
      {
        scale -= (mSpeed * deltaTime);
        if (scale < finalScale)
        {
          scale = finalScale;
        }
      }
      mAnimator->GetOwner()->SetScale(scale);
      return true;
    }
  }

  return false;
}

void TransformAnimation::SetFinalPosition(Vector2 finalPosition)
{
  if (!mFinalPosition)
  {
    mFinalPosition = new Vector2 (finalPosition);
  }
  else
  {
    (*mFinalPosition) = finalPosition;
  }
}

void TransformAnimation::SetFinalRotation(float finalRotation)
{
  if (!mFinalRotation)
  {
    mFinalRotation = new float (finalRotation);
  }
  else
  {
    (*mFinalRotation) = finalRotation;
  }
}

void TransformAnimation::SetFinalScale(float finalScale)
{
  if (!mFinalScale)
  {
    mFinalScale = new float (finalScale);
  }
  else
  {
    (*mFinalScale) = finalScale;
  }
}
