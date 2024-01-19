//
// Created by shehbaz on 1/18/2024.
//

#include "BackButton.h"
#include "BoxCollider.h"
#include "SpriteComponent.h"

BackButton::BackButton(Game *game, Game::GameState gameState)
:Actor(game, gameState)
{
}

BackButton::~BackButton()
{
  UnloadTexture(mOnHoverTexture);
  UnloadTexture(mOffHoverTexture);
}

void BackButton::UpdateActor(float deltaTime)
{
  Actor::UpdateActor(deltaTime);

  auto boxCollider = (BoxCollider*)GetComponent("BoxCollider");
  if (boxCollider)
  {
    auto spriteComponent = (SpriteComponent*)GetComponent("SpriteComponent");
    if (spriteComponent)
    {
      if (boxCollider->OnHover())
      {
        spriteComponent->SetTexture(mOnHoverTexture);
        int value = boxCollider->OnClick();
        if (value == MOUSE_BUTTON_LEFT)
        {
          GetGame()->SetGameState(Game::MENU);
        }
      }
      else
      {
        spriteComponent->SetTexture(mOffHoverTexture);
      }
    }
    else
    {
      TraceLog(LOG_ERROR, "No SpriteComponent on BackButton!!!");
    }
  }
  else
  {
    TraceLog(LOG_ERROR, "No BoxCollider on BackButton!!!");
  }
}
