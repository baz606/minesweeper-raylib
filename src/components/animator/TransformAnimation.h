//
// Created by shehbaz on 1/15/2024.
//

#pragma once

#include "raylib.h"
#include "Animation.h"

// Animation based on an actor's transform. i.e. position, rotation and scale
class TransformAnimation : public Animation
{
public:
  TransformAnimation(Animator* animator, float speed);
  ~TransformAnimation() override;

  bool Play(float deltaTime) override;

  // Setters/Getters
  void SetFinalPosition(Vector2 finalPosition);
  void SetFinalRotation(float finalRotation);
  void SetFinalScale(float finalScale);

private:
  // Transform
  Vector2* mFinalPosition;
  float* mFinalScale;
  float* mFinalRotation;

  bool UpdateRotation(float deltaTime);
  bool UpdatePosition(float deltaTime);
  bool UpdateScale(float deltaTime);
};
