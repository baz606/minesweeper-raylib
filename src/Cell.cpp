//
// Created by shehbaz on 12/6/2023.
//

//#include <string>
#include "Cell.h"
#include "Game.h"
#include "Grid.h"
#include "RectangleMeshComponent.h"
#include "LineMeshComponent.h"
#include "TextComponent.h"

Cell::Cell(Game *game, Game::GameState gameState, Grid *grid)
:Actor(game, gameState)
,mGrid(grid)
{
  mCellType = UNEXPOSE;
  mNumOfMines = 0;
}

void Cell::SetupComponents()
{
  // Add rectangle mesh component for the color of the cells
  auto mesh = new RectangleMeshComponent("RectangleMeshComponent", this, 1);
  mesh->SetColor(DARKGRAY);
  mesh->SetBorderColor(BLACK);
  mesh->SetBorderThickness(3.f);
  mesh->SetWidth(Cell::LENGTH);
  mesh->SetHeight(Cell::LENGTH);

  auto textComp = new TextComponent("TextComponent", this, 2);
  textComp->SetColor(RAYWHITE);
  textComp->SetFont(GetFontDefault());
  textComp->SetFontSize(50.f);
  textComp->SetSpacing(0.f);
  textComp->SetText(std::to_string(this->GetNumOfMines()));
  textComp->SetIsShow(false);

  // Add line mesh component for the sealed state of cells
  auto lineMesh = new LineMeshComponent("LineMeshComponent", this, 2);
  lineMesh->SetThickness(3.f);
  lineMesh->SetColor(BLACK);
  lineMesh->SetLinePair({ this->GetPosition().x - (Cell::LENGTH / 2), this->GetPosition().y - (Cell::LENGTH / 2) },
                        { this->GetPosition().x + (Cell::LENGTH / 2), this->GetPosition().y + (Cell::LENGTH / 2) });
  lineMesh->SetLinePair({ this->GetPosition().x + (Cell::LENGTH / 2), this->GetPosition().y - (Cell::LENGTH / 2) },
                        { this->GetPosition().x - (Cell::LENGTH / 2), this->GetPosition().y + (Cell::LENGTH / 2) });

}

void Cell::UpdateActor(float deltaTime)
{
  auto mesh = (RectangleMeshComponent*)(GetComponent("RectangleMeshComponent"));
  auto lineMesh = (LineMeshComponent*)(GetComponent("LineMeshComponent"));
  switch (mCellType)
  {
    case MINE:
    case UNEXPOSE:
      mesh->SetColor(DARKGRAY);
      lineMesh->SetIsShow(false);
      break;
    case EXPOSE:
    case ADJACENT:
      mesh->SetColor(BLUE);
      lineMesh->SetIsShow(false);
      break;
    case SEALED:
    case MINE_SEALED:
      mesh->SetColor(PURPLE);
      lineMesh->SetIsShow(true);
      break;
    case MINE_EXPOSE:
      mesh->SetColor(RED);
      break;
    default:
      mesh->SetColor(DARKGRAY);
  }
}

void Cell::SetCellType(CellType cellType)
{
  mCellType = cellType;
}

void Cell::SetIndex(int x, int y)
{
  mIndex.x = x;
  mIndex.y = y;
}

void Cell::Reset()
{
  mCellType = UNEXPOSE;
  auto textComp = (TextComponent*)(GetComponent("TextComponent"));
  if (textComp)
  {
    textComp->SetIsShow(false);
  }
  else
  {
    printf("TextComponent is null!!!\n");
  }
  mNumOfMines = 0;
}
