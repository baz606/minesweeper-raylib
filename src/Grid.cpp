//
// Created by shehbaz on 12/10/2023.
//

#include <ctime>
#include <cmath>
#include "Grid.h"
#include "Game.h"
#include "Cell.h"
#include "RectangleMeshComponent.h"
#include "TextComponent.h"

Grid::Grid(Game* game, int rows, int columns, int mines)
:Actor(game)
,mRows(rows)
,mColumns(columns)
,mMines(mines)
{
}

void Grid::Initialize()
{
  int padding = 10;
  this->SetPosition(((float)(Cell::LENGTH * mRows) + (float)padding) / 2,
                    ((float)(Cell::LENGTH * mColumns) + (float)padding) / 2);

  auto gridMesh = new RectangleMeshComponent("RectangleMeshComponent", this, 0);
  gridMesh->SetColor(RAYWHITE);
  gridMesh->SetWidth((Cell::LENGTH * mRows) + padding);
  gridMesh->SetHeight((Cell::LENGTH * mColumns) + padding);

  mCellList.resize(mRows);
  for (int i = 0; i < mRows; ++i)
  {
    mCellList[i].resize(mColumns);
    for (int j = 0; j < mColumns; ++j)
    {
      auto cell = new Cell(GetGame(), this);
      cell->SetPosition(((float)(j * Cell::LENGTH) + ((float)Cell::LENGTH / 2)),
                        (float)(i * Cell::LENGTH) + ((float)Cell::LENGTH / 2));
      cell->SetIndex(i, j);
      cell->SetCellType(UNEXPOSE);
      mCellList[i][j] = cell;

      auto mesh = new RectangleMeshComponent("RectangleMeshComponent", cell, 1);
      mesh->SetColor(DARKGRAY);
      mesh->SetBorderColor(BLACK);
      mesh->SetBorderThickness(3.f);
      mesh->SetWidth(Cell::LENGTH);
      mesh->SetHeight(Cell::LENGTH);
    }
  }
  SetMines();
}

void Grid::UpdateActor(float deltaTime)
{
  Actor::UpdateActor(deltaTime);
}

void Grid::ProcessInput(int mouseX, int mouseY)
{
  if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
  {
    int i = std::lround(mouseY / Cell::LENGTH);
    int j = std::lround(mouseX / Cell::LENGTH);
    if (i >= 0 && i < mRows && j >= 0 && j < mColumns)
    {
      Expose(mCellList[i][j]);
    }
  }
  else if(IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
  {
    int i = std::lround(mouseY / Cell::LENGTH);
    int j = std::lround(mouseX / Cell::LENGTH);
    if (i >= 0 && i < mRows && j >= 0 && j < mColumns)
    {
      ToggleSeal(mCellList[i][j]);
    }
  }
}

void Grid::ToggleSeal(Cell* cell)
{
  if (cell->GetCellType() == UNEXPOSE)
  {
    cell->SetCellType(SEALED);
    return;
  }
  else if (cell->GetCellType() == MINE)
  {
    cell->SetCellType(MINE_SEALED);
    return;
  }

  if (cell->GetCellType() == SEALED)
  {
    cell->SetCellType(UNEXPOSE);
  }
  else if (cell->GetCellType() == MINE_SEALED)
  {
    cell->SetCellType(MINE);
  }
}

void Grid::SetMines()
{
  int i = 0, j = 0, k = 0;
  SetRandomSeed(time(nullptr));
  mMineList.clear();
  while (k < mMines)
  {
    i = GetRandomValue(0, mRows - 1);
    j = GetRandomValue(0, mColumns - 1);
    // Set Mine cell
    if (mCellList[i][j]->GetCellType() != MINE)
    {
      mCellList[i][j]->SetCellType(MINE);
      mMineList.push_back(mCellList[i][j]);
    }
    else
    {
      // This randomly selected cell is either a MINE or ADJACENT cell already
      continue;
    }
    k++;
  }
}

int Grid::GetAdjacentCellsInfo(Cell *cell, std::vector<Cell *>& adjacentCells)
{
  int numOfMines = 0;

  const int x = cell->GetIndex().x;
  const int y = cell->GetIndex().y;
  // Check top and bottom row
  for (int i = x - 1, z = x + 1, j = y - 1; j < y + 2; j++)
  {
    if (i >= 0 || z < mRows)
    {
      if (i >= 0 && j >= 0 && j < mColumns)
      {
        // Valid adjacent cell
        adjacentCells.push_back(mCellList[i][j]);
        if (mCellList[i][j]->GetCellType() == MINE)
        {
          numOfMines++;
        }
      }
      if (z < mRows && j >= 0 && j < mColumns)
      {
        // Valid adjacent cell
        adjacentCells.push_back(mCellList[z][j]);
        if (mCellList[z][j]->GetCellType() == MINE)
        {
          numOfMines++;
        }
      }
    }
    else
    {
      // No top or bottom row
      break;
    }
  }
  // Check left of the cell
  if ((y - 1) >= 0)
  {
    adjacentCells.push_back(mCellList[x][y - 1]);
    if (mCellList[x][y - 1]->GetCellType() == MINE)
    {
      numOfMines++;
    }
  }
  // Check right of the cell
  if ((y + 1) < mColumns)
  {
    adjacentCells.push_back(mCellList[x][y + 1]);
    if (mCellList[x][y + 1]->GetCellType() == MINE)
    {
      numOfMines++;
    }
  }
  return numOfMines;
}

void Grid::Expose(Cell *cell)
{
  if (cell->GetCellType() == MINE)
  {
    // End game
    printf("YOU CLICKED A MINE! GAME OVER!\n");
  }
  else if (cell->GetCellType() == UNEXPOSE)
  {
    // Check if its a normal cell
    std::vector<Cell*> adjacentCells;
    int numOfMines = GetAdjacentCellsInfo(cell, adjacentCells);
    if (numOfMines > 0)
    {
      // This is an adjacent cell (Base case)
      // We change its cell type and add a text component
      cell->SetCellType(ADJACENT);
      cell->SetNumOfMines(numOfMines);
      auto textComp = new TextComponent("TextComponent", cell, 2);
      textComp->SetColor(RAYWHITE);
      textComp->SetFont(GetFontDefault());
      textComp->SetFontSize(40.f);
      textComp->SetSpacing(0.f);
      textComp->SetText(std::to_string(cell->GetNumOfMines()));
    }
    else
    {
      // We have a normal cell
      // We change its state and loop over adjacentCells and recursively expose them
      cell->SetCellType(EXPOSE);
      for (auto adjCell : adjacentCells)
      {
        if (adjCell->GetCellType() == UNEXPOSE)
        {
          Expose(adjCell);
        }
      }
    }
  }
}
