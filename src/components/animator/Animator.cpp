//
// Created by shehbaz on 1/15/2024.
//

#include <algorithm>
#include "Animator.h"
#include "Animation.h"
#include "../../actors/Actor.h"

Animator::Animator(const std::string &name, Actor *owner, int updateOrder)
: Component(name, owner, updateOrder)
,mCurrentAnimIndex(0)
,mIsPlay(false)
,mIsIncrement(false)
{
}

Animator::~Animator()
{
  while (mAnimations.empty())
  {
    delete mAnimations.back();
  }
}

void Animator::Update(float deltaTime)
{
  Component::Update(deltaTime);

  if (mIsPlay)
  {
    if (mCurrentAnimIndex < mAnimations.size())
    {
      if (mAnimations[mCurrentAnimIndex]->Play(deltaTime))
      {
        mIsIncrement = false;
        return;
      }
      mCurrentAnimIndex++;
      mIsIncrement = true;
    }
    else
    {
      mIsPlay = false;
      mIsIncrement = false;
    }
  }
}

void Animator::AddAnimation(Animation *animation)
{
  mAnimations.emplace_back(animation);
}

void Animator::RemoveAnimation(Animation *animation)
{
  auto iter = std::find(mAnimations.begin(), mAnimations.end(), animation);
  if (iter != mAnimations.end())
  {
    mAnimations.erase(iter);
  }
}

void Animator::Reset()
{
  // Reset animations
  TraceLog(LOG_DEBUG, "Reset Animations");
  mCurrentAnimIndex = 0;
  mIsPlay = true;
}

void Animator::Play()
{
  mIsPlay = true;
}
