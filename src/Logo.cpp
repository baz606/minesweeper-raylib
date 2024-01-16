//
// Created by shehbaz on 1/14/2024.
//

#include "Logo.h"
#include "TextComponent.h"
#include "Animator.h"
#include "TransformAnimation.h"

Logo::Logo(Game *game, Game::GameState gameState)
:Actor(game, gameState)
{
}

void Logo::Init()
{
  // Add Text component for logo
  auto textComp = new TextComponent("TextComponent", this);
  textComp->SetText("@baz606");
  textComp->SetColor(VIOLET);
  textComp->SetFont(GetGame()->GetFont());
  textComp->SetFontSize(200);
  textComp->SetSpacing(0);

  // Add Animation
  auto animator = new Animator("Animator", this);

  auto transformAnimation1 = new TransformAnimation(animator, 2000.f);
  transformAnimation1->SetFinalPosition({ GetGame()->GetScreenWidth() / 2.f, GetGame()->GetScreenHeight() / 2.f });
  auto transformAnimation2 = new TransformAnimation(animator, 100.f);
  transformAnimation2->SetFinalRotation(180.f);
  auto transformAnimation3 = new TransformAnimation(animator, 100.f);
  transformAnimation3->SetFinalRotation(0.f);

  // Play all animations added above
  animator->Play();
}
