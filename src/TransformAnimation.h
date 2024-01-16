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

  bool Play() override;

  // Setters/Getters
  void SetFinalPosition(Vector2 finalPosition);
  void SetFinalRotation(float finalRotation);
  void SetFinalScale(float finalScale);

private:
  // Transform
  Vector2* mFinalPosition;
  float* mFinalScale;
  float* mFinalRotation;

  bool UpdateRotation();

  bool UpdatePosition();

  bool UpdateScale();
};
