//
// Created by shehbaz on 1/18/2024.
//

#include "BoxCollider.h"
#include "../actors/Actor.h"
#include "SpriteComponent.h"

BoxCollider::BoxCollider(const std::string &name, Actor *owner, int updateOrder)
:Component(name, owner, updateOrder)
{
  mCollider = nullptr;
}

BoxCollider::~BoxCollider()
{
  // Deallocate memory
  delete mCollider;
}

void BoxCollider::SetCollider(float x, float y, float width, float height)
{
  mCollider = new Rectangle (x, y, width, height);
}

void BoxCollider::Update(float deltaTime)
{
  Component::Update(deltaTime);
}

bool BoxCollider::OnHover()
{
  if (mCollider)
  {
    Rectangle mouseRect = { (float)GetMouseX(), (float)GetMouseY(), 0, 0 };
    return CheckCollisionRecs(mouseRect, *mCollider);
  }
  return false;
}

int BoxCollider::OnClick()
{
  if (OnHover())
  {
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
      return MOUSE_BUTTON_LEFT;
    }
    else if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
    {
      return MOUSE_BUTTON_RIGHT;
    }
    else if (IsMouseButtonReleased(MOUSE_BUTTON_MIDDLE))
    {
      return MOUSE_BUTTON_MIDDLE;
    }
  }
  // Return -1 which is considered false in c++
  return -1;
}
