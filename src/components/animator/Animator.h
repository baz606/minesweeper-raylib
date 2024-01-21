//
// Created by shehbaz on 1/15/2024.
//

#pragma once

#include <vector>

#include "../Component.h"
#include "../../actors/Actor.h"

class Animator : public Component
{
public:
  Animator(const std::string& name, Actor* owner, int updateOrder = 100);
  ~Animator() override;

  void Update(float deltaTime) override;

  void AddAnimation(class Animation* animation);
  void RemoveAnimation(class Animation* animation);

  void Play();
  void Reset();
  [[nodiscard]] bool IsIncrementAnim() const { return mIsIncrement; }
  // Check if all animations have been played
  [[nodiscard]] bool IsDone() const { return !mIsPlay; }

private:
  std::vector<class Animation*> mAnimations;
  int mCurrentAnimIndex;
  bool mIsPlay;
  // This bool lets us know when an animation in mAnimations is done playing
  bool mIsIncrement;
};
