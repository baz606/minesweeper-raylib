//
// Created by shehbaz on 1/15/2024.
//

#pragma once

#include <vector>

#include "Component.h"
#include "Actor.h"

class Animator : public Component
{
public:
  Animator(const std::string& name, Actor* owner, int updateOrder = 100);
  ~Animator() override;

  void Update(float deltaTime) override;

  void AddAnimation(class Animation* animation);
  void RemoveAnimation(class Animation* animation);
  void Reset();

private:
  std::vector<class Animation*> mAnimations;
  int mCurrentAnimIndex;
};
