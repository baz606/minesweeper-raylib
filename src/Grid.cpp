//
// Created by shehbaz on 12/10/2023.
//

#include <ctime>
#include <cmath>
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
  int padding = 10;
  this->SetPosition(((float)(Cell::LENGTH * mRows) + (float)padding) / 2,
                    ((float)(Cell::LENGTH * mColumns) + (float)padding) / 2);

  auto gridMesh = new MeshComponent("MeshComponent", this, 0);
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
      cell->SetPosition(((float)(j * Cell::LENGTH) + ((float)Cell::LENGTH / 2)), (float)(i * Cell::LENGTH) + ((float)Cell::LENGTH / 2));

      auto mesh = new MeshComponent("MeshComponent", cell, 1);
      mesh->SetColor(DARKGRAY);
      mesh->SetBorderColor(BLACK);
      mesh->SetBorderThickness(3.f);
      mesh->SetWidth(Cell::LENGTH);
      mesh->SetHeight(Cell::LENGTH);

      mCellList[i][j] = cell;
    }
  }
  SetMines();
}

void Grid::UpdateActor(float deltaTime)
{
  Actor::UpdateActor(deltaTime);

  if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
  {
    ProcessMouse(GetMouseX(), GetMouseY());
  }
}
void Grid::ProcessMouse(int mouseX, int mouseY)
{
  int i = std::lround(mouseY / Cell::LENGTH);
  int j = std::lround(mouseX / Cell::LENGTH);
  if (i >= 0 && i < mRows && j >= 0 && j < mColumns)
  {
    printf("Selected on cell at: (%d, %d)\n", i, j);
    printf("Number of mines: %d\n", mCellList[i][j]->GetNumOfMines());
//    Expose(grid[i][j]);
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
      SetAdjacentCellsAround(i, j);
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

void Grid::SetAdjacentCellsAround(int i, int j)
{
  std::vector<Cell*> adjacentCells;
  GetAdjacentCellsFor(i, j, adjacentCells);

  for (auto adjCell : adjacentCells)
  {
    if(adjCell->GetCellType() != MINE)
    {
      // If not a mine cell, set adjacent cell type and increment the number of mines around it
      adjCell->SetCellType(ADJACENT_UNEXPOSE);
    }
  }
}

void Grid::GetAdjacentCellsFor(int i, int j, std::vector<Cell*> &adjacentCells)
{
  const int x = i;
  const int y = j;
  // Check top and bottom row
  for (int i = x - 1, z = x + 1, j = y - 1; j < y + 2; j++)
  {
    if (i >= 0 || z < mRows)
    {
      if (i >= 0 && j >= 0 && j < mColumns)
      {
        // Valid adjacent cell
        adjacentCells.push_back(mCellList[i][j]);
      }
      if (z < mRows && j >= 0 && j < mColumns)
      {
        // Valid adjacent cell
        adjacentCells.push_back(mCellList[z][j]);
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
  }
  // Check right of the cell
  if ((y + 1) < mColumns)
  {
    adjacentCells.push_back(mCellList[x][y + 1]);
  }
}