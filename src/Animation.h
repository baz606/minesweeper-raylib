//
// Created by shehbaz on 1/15/2024.
//

#pragma once

// Base class for all animation types
class Animation
{
public:
  Animation(class Animator* animator, float speed);
  virtual ~Animation();

  virtual bool Play(float deltaTime) = 0;

  // Setters/Getters
  void SetSpeed(float speed) { mSpeed = speed; }
  [[nodiscard]] float GetSpeed() const { return mSpeed; }
  void SetAnimator(Animator* animator) { mAnimator = animator; }
  [[nodiscard]] Animator* GetAnimator() const { return mAnimator; }

protected:
  float mSpeed;
  Animator* mAnimator;
};
