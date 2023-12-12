//
// Created by shehbaz on 12/10/2023.
//

#include <ctime>
#include "Grid.h"
#include "Game.h"
#include "Cell.h"
#include "MeshComponent.h"

Grid::Grid(Game* game, int rows, int columns, int mines)
:Actor(game)
,mRows(rows)
,mColumns(columns)
,mMines(mines)
{
}

void Grid::Initialize()
{
  auto mesh = new MeshComponent("MeshComponent", this, RAYWHITE, RAYWHITE, 0, 0);
  float padding = 10.f;
  mesh->SetRectangle(0.f, 0.f, (float)(mRows * Cell::LENGTH) + padding, (float)(mColumns * Cell::LENGTH) + padding);

  mCellList.resize(mRows);
  for (int i = 0; i < mRows; ++i)
  {
    mCellList[i].resize(mColumns);
    for (int j = 0; j < mColumns; ++j)
    {
      auto cell = new Cell(GetGame(), this);
      auto meshComponent = new MeshComponent("MeshComponent", cell, DARKGRAY, BLACK, 3.f, 1);
      meshComponent->SetRectangle(j * Cell::LENGTH, i * Cell::LENGTH, Cell::LENGTH, Cell::LENGTH);
      mCellList[i][j] = cell;
    }
  }
  SetMines();
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
    if (mCellList[i][j]->GetCellType() == UNEXPOSE)
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
//  for (auto cell : mineCells)
//  {
//    // Set adjacent cells around this mine cell
//    SetAdjacentCellsAround(cell);
//  }
}
