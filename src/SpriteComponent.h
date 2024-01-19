//
// Created by shehbaz on 1/18/2024.
//

#pragma once

#include "DrawComponent.h"
#include "raylib.h"

class SpriteComponent : public DrawComponent
{
public:
  SpriteComponent(const char *fileName, const std::string& name, class Actor* owner, int drawOrder = 100);
  ~SpriteComponent() override;

  void Draw() override;

  // Setters/Getters
  void SetColorTint(Color tint) { mTint = tint; }
  [[nodiscard]] Color GetColorTint() const { return mTint; }
  void SetTexture(const Texture2D& texture);
  void SetTexture(const char* fileName);
  [[nodiscard]] Texture2D GetTexture() const { return mTexture; }

private:
  Texture2D mTexture;
  Color mTint;
};
