//
// Created by shehbaz on 1/18/2024.
//

#include "SpriteComponent.h"
#include "../actors/Actor.h"

SpriteComponent::SpriteComponent(const std::string& name, Actor *owner, int drawOrder)
:DrawComponent(name, owner, drawOrder)
{
  mTint = LIGHTGRAY;
}

SpriteComponent::~SpriteComponent()
{
  UnloadTexture(mTexture);
}

void SpriteComponent::Draw()
{
  if (mIsShow)
  {
    Rectangle source = { 0.0f, 0.0f, (float)mTexture.width, (float)mTexture.height };
    Rectangle dest = { mOwner->GetPosition().x, mOwner->GetPosition().y, (float)mTexture.width * mOwner->GetScale(), (float)mTexture.height * mOwner->GetScale() };
    Vector2 origin = { ((float)mTexture.width / 2.f) * mOwner->GetScale(), ((float)mTexture.height / 2.f) * mOwner->GetScale() };

    DrawTexturePro(mTexture, source, dest, origin, mOwner->GetRotation(), mTint);
  }
}

void SpriteComponent::SetTexture(const Texture2D &texture)
{
  mTexture = texture;
}

void SpriteComponent::SetTexture(const char *fileName)
{
  // Unload current texture
  UnloadTexture(mTexture);
  // Load texture from file
  mTexture = LoadTexture(fileName);
}
