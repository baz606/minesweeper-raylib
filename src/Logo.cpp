//
// Created by shehbaz on 1/14/2024.
//

#include "Logo.h"
#include "TextComponent.h"

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
}
