//
// Created by shehbaz on 1/20/2024.
//

#include "Logo.h"
#include "../components/TextComponent.h"
#include "../components/animator/Animator.h"
#include "../components/animator/TransformAnimation.h"

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
  // Add Animation to logo
  auto animator = new Animator("Animator", this);
  auto anim1 = new TransformAnimation(animator, 2000.f);
  anim1->SetFinalPosition({ GetGame()->GetScreenWidth() / 2.f, GetGame()->GetScreenHeight() / 2.f });
  anim1->SetFinalRotation(20.f);
  auto anim2 = new TransformAnimation(animator, 200.f);
  anim2->SetFinalRotation(-20.f);
  auto anim3 = new TransformAnimation(animator, 50.f);
  anim3->SetFinalRotation(20.f);
  auto anim4 = new TransformAnimation(animator, 25.f);
  anim4->SetFinalRotation(0.f);
  // Play all animations added above
  animator->Play();
}

void Logo::UpdateActor(float deltaTime)
{
  Actor::UpdateActor(deltaTime);

  auto animator = (Animator*)GetComponent("Animator");
  if (animator)
  {
    if (animator->IsIncrementAnim())
    {
      GetGame()->PlaySoundFromMap("logo-bounce.wav");
    }
  }
  else
  {
    TraceLog(LOG_ERROR, "Animator not present in Logo!!!");
  }
}
