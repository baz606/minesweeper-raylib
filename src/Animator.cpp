//
// Created by shehbaz on 1/15/2024.
//

#include <algorithm>
#include "Animator.h"
#include "Animation.h"
#include "Actor.h"

Animator::Animator(const std::string &name, Actor *owner, int updateOrder)
:Component(name, owner, updateOrder)
,mCurrentAnimIndex(0)
{
}

Animator::~Animator()
{
  for (auto anim : mAnimations)
  {
    delete anim;
  }
}

void Animator::Update(float deltaTime)
{
  Component::Update(deltaTime);
  if (mCurrentAnimIndex < mAnimations.size())
  {
    if (mAnimations[mCurrentAnimIndex]->Play())
    {
      return;
    }
    mCurrentAnimIndex++;
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
  mCurrentAnimIndex = 0;
}