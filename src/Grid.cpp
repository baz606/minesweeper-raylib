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
#include "LineMeshComponent.h"

Grid::Grid(Game* game, int rows, int columns, int mines)
:Actor(game)
,mRows(rows)
,mColumns(columns)
,mMines(mines)
,mTotalSeals(mines)
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

      // Add rectangle mesh component for the color of the cells
      auto mesh = new RectangleMeshComponent("RectangleMeshComponent", cell, 1);
      mesh->SetColor(DARKGRAY);
      mesh->SetBorderColor(BLACK);
      mesh->SetBorderThickness(3.f);
      mesh->SetWidth(Cell::LENGTH);
      mesh->SetHeight(Cell::LENGTH);

      auto textComp = new TextComponent("TextComponent", cell, 2);
      textComp->SetColor(RAYWHITE);
      textComp->SetFont(GetFontDefault());
      textComp->SetFontSize(40.f);
      textComp->SetSpacing(0.f);
      textComp->SetText(std::to_string(cell->GetNumOfMines()));
      textComp->SetIsShow(false);

      // Add line mesh component for the sealed state of cells
      auto lineMesh = new LineMeshComponent("LineMeshComponent", cell, 2);
      lineMesh->SetThickness(3.f);
      lineMesh->SetColor(BLACK);
      lineMesh->SetLinePair({ cell->GetPosition().x - (Cell::LENGTH / 2), cell->GetPosition().y - (Cell::LENGTH / 2) },
                            { cell->GetPosition().x + (Cell::LENGTH / 2), cell->GetPosition().y + (Cell::LENGTH / 2) });
      lineMesh->SetLinePair({ cell->GetPosition().x + (Cell::LENGTH / 2), cell->GetPosition().y - (Cell::LENGTH / 2) },
                            { cell->GetPosition().x - (Cell::LENGTH / 2), cell->GetPosition().y + (Cell::LENGTH / 2) });
    }
  }
  SetMines();
}

void Grid::Reset()
{
  for (auto& row : mCellList)
  {
    for (auto cell : row)
    {
      // Reset cell to original state
      cell->Reset();
    }
  }
  // Re-setup mines randomly
  SetMines();
  GetGame()->SetGameState(Game::PLAYING);
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
  if (cell->GetCellType() == UNEXPOSE && mTotalSeals > 0)
  {
    cell->SetCellType(SEALED);
    mTotalSeals--;
    return;
  }
  else if (cell->GetCellType() == MINE && mTotalSeals > 0)
  {
    cell->SetCellType(MINE_SEALED);
    mTotalSeals--;
    CheckForWin();
    return;
  }

  if (cell->GetCellType() == SEALED)
  {
    cell->SetCellType(UNEXPOSE);
    mTotalSeals++;
  }
  else if (cell->GetCellType() == MINE_SEALED)
  {
    cell->SetCellType(MINE);
    mTotalSeals++;
  }
}

void Grid::SetMines()
{
  int i = 0, j = 0, k = 0;
  SetRandomSeed(time(nullptr));
  mMineList.clear();
  mTotalSeals = mMines;
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
}

int Grid::GetAdjacentCells(Cell *cell, std::vector<Cell*>& adjacentCells)
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
        if (mCellList[i][j]->GetCellType() == MINE || mCellList[i][j]->GetCellType() == MINE_SEALED)
        {
          numOfMines++;
        }
      }
      if (z < mRows && j >= 0 && j < mColumns)
      {
        // Valid adjacent cell
        adjacentCells.push_back(mCellList[z][j]);
        if (mCellList[z][j]->GetCellType() == MINE || mCellList[z][j]->GetCellType() == MINE_SEALED)
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
    if (mCellList[x][y - 1]->GetCellType() == MINE || mCellList[x][y - 1]->GetCellType() == MINE_SEALED)
    {
      numOfMines++;
    }
  }
  // Check right of the cell
  if ((y + 1) < mColumns)
  {
    adjacentCells.push_back(mCellList[x][y + 1]);
    if (mCellList[x][y + 1]->GetCellType() == MINE || mCellList[x][y + 1]->GetCellType() == MINE_SEALED)
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
    GetGame()->SetGameState(Game::GAME_OVER);
    for (auto mine : mMineList)
    {
      mine->SetCellType(MINE_EXPOSE);
    }
  }
  else if (cell->GetCellType() == UNEXPOSE)
  {
    // Check if its a normal cell
    std::vector<Cell*> adjacentCells;
    int numOfMines = GetAdjacentCells(cell, adjacentCells);
    if (numOfMines > 0)
    {
      // This is an adjacent cell (Base case)
      // We change its cell type and add a text component
      cell->SetCellType(ADJACENT);
      cell->SetNumOfMines(numOfMines);
      // Check if this cell already has a TextComponent
      auto textComp = reinterpret_cast<TextComponent*>(cell->GetComponent("TextComponent"));
      if (textComp)
      {
        textComp->SetColor(RAYWHITE);
        textComp->SetFont(GetGame()->GetFont());
        textComp->SetFontSize(70.f);
        textComp->SetSpacing(0.f);
        textComp->SetText(std::to_string(cell->GetNumOfMines()));
        textComp->SetIsShow(true);
      }
      else
      {
        printf("TextComponent is null!!!\n");
      }
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

void Grid::CheckForWin()
{
  for (auto mine : mMineList)
  {
    if (mine->GetCellType() == MINE)
    {
      // There is at least one mine cell that is not sealed
      return;
    }
  }
  // Once we get to this point, we know all mines are set to MINE_SEALED state.
  // Hence, set game condition to WIN
  GetGame()->SetGameState(Game::WIN);
}
