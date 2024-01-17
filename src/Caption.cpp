//
// Created by shehbaz on 1/16/2024.
//

#include "Caption.h"
#include "TextComponent.h"
#include "Animator.h"
#include "FlashingAnimation.h"

Caption::Caption(Game *game, Game::GameState gameState)
:Actor(game, gameState)
{
}

void Caption::Init()
{
  // Add Text component for logo
  auto textComp = new TextComponent("TextComponent", this);
  textComp->SetText("PRESS ANY KEY TO CONTINUE...");
  textComp->SetColor(BLACK);
  textComp->SetFont(GetGame()->GetFont());
  textComp->SetFontSize(80);
  textComp->SetSpacing(0);
  textComp->SetIsShow(false);

  // Add Animation
  auto animator = new Animator("Animator", this);
  new FlashingAnimation(animator, textComp, 1.f);
}
