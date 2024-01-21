//
// Created by shehbaz on 12/10/2023.
//

#include <ctime>
#include <cmath>
#include <cstring>
#include "Grid.h"
#include "../Game.h"
#include "Cell.h"
#include "../components/RectangleMeshComponent.h"
#include "../components/TextComponent.h"
#include "../components/LineMeshComponent.h"

Grid::Grid(Game* game, Game::GameState gameState, int rows, int columns, int mines)
:Actor(game, gameState)
,mRows(rows)
,mColumns(columns)
,mMines(mines)
,mTotalSeals(mines)
,bufferIndex(0)
,currentTime(0.f)
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
      auto cell = new Cell(GetGame(), Game::PLAYING, this);
      cell->SetPosition(((float)(j * Cell::LENGTH) + ((float)Cell::LENGTH / 2)),
                        (float)(i * Cell::LENGTH) + ((float)Cell::LENGTH / 2));
      cell->SetIndex(i, j);
      cell->SetCellType(UNEXPOSE);
      mCellList[i][j] = cell;
      // Setup required components to this cell actor
      cell->SetupComponents();
    }
  }
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
  // Check reveal mines
  char c = (char)GetCharPressed();
  if(c > 0)
  {
    buffer[bufferIndex] = c;
    buffer[bufferIndex + 1] = '\0';
    bufferIndex++;
    TraceLog(LOG_DEBUG,"BUFFER: %s\n", buffer);
    if (bufferIndex > 4)
    {
      if (strcmp(buffer, "siuuu") == 0)
      {
        GetGame()->PlaySoundFromMap("reveal-mines.mp3");
        // Reveal all mines
        for (auto mine : mMineList)
        {
          mine->SetCellType(MINE_EXPOSE);
        }
      }
      for (char & i : buffer)
      {
        i = '\0';
      }
      bufferIndex = 0;
    }
    currentTime = 0.f;
  }
  else
  {
    float deltaTime = GetFrameTime();
    currentTime += deltaTime;
    if (currentTime > MAX_TIME)
    {
      // Check if buffer char array has at least one element
      if (bufferIndex > 0)
      {
        printf("Clearing buffer char array\n");
        // Clear out the buffer
        for (char & i : buffer)
        {
          i = '\0';
        }
        bufferIndex = 0;
      }
      currentTime = 0.f;
    }
  }
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
    GetGame()->PlaySoundFromMap("toggle-seal-click.wav", 0.5f);

    return;
  }
  else if (cell->GetCellType() == MINE && mTotalSeals > 0)
  {
    cell->SetCellType(MINE_SEALED);
    mTotalSeals--;
    GetGame()->PlaySoundFromMap("toggle-seal-click.wav", 0.5f);
    CheckForWin();

    return;
  }

  if (cell->GetCellType() == SEALED)
  {
    cell->SetCellType(UNEXPOSE);
    mTotalSeals++;
    GetGame()->PlaySoundFromMap("toggle-seal-click.wav", 0.5f);
  }
  else if (cell->GetCellType() == MINE_SEALED)
  {
    cell->SetCellType(MINE);
    mTotalSeals++;
    GetGame()->PlaySoundFromMap("toggle-seal-click.wav", 0.5f);
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
        if (mCellList[i][j]->GetCellType() == MINE || mCellList[i][j]->GetCellType() == MINE_SEALED || mCellList[i][j]->GetCellType() == MINE_EXPOSE)
        {
          numOfMines++;
        }
      }
      if (z < mRows && j >= 0 && j < mColumns)
      {
        // Valid adjacent cell
        adjacentCells.push_back(mCellList[z][j]);
        if (mCellList[z][j]->GetCellType() == MINE || mCellList[z][j]->GetCellType() == MINE_SEALED || mCellList[z][j]->GetCellType() == MINE_EXPOSE)
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
    if (mCellList[x][y - 1]->GetCellType() == MINE || mCellList[x][y - 1]->GetCellType() == MINE_SEALED || mCellList[x][y - 1]->GetCellType() == MINE_EXPOSE)
    {
      numOfMines++;
    }
  }
  // Check right of the cell
  if ((y + 1) < mColumns)
  {
    adjacentCells.push_back(mCellList[x][y + 1]);
    if (mCellList[x][y + 1]->GetCellType() == MINE || mCellList[x][y + 1]->GetCellType() == MINE_SEALED || mCellList[x][y + 1]->GetCellType() == MINE_EXPOSE)
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
    TraceLog(LOG_DEBUG, "YOU CLICKED A MINE! GAME OVER!");
    GetGame()->SetGameState(Game::GAME_OVER);
    for (auto mine : mMineList)
    {
      mine->SetCellType(MINE_EXPOSE);
    }
    GetGame()->PlaySoundFromMap("mine-click.wav");
  }
  else if (cell->GetCellType() == UNEXPOSE)
  {
    GetGame()->PlaySoundFromMap("cell-click.wav", 2.f);
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
        textComp->SetText(std::to_string(cell->GetNumOfMines()));
        textComp->SetIsShow(true);
      }
      else
      {
        TraceLog(LOG_ERROR, "TextComponent is null!!!");
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
    CheckForWin();
  }
}

void Grid::CheckAllMinesSealed()
{
  // Check whether all mines are sealed
  if (GetGame()->GetGameState() != Game::WIN)
  {
    for (auto mine : mMineList)
    {
      if (mine->GetCellType() != MINE_SEALED)
      {
        // There is at least one mine cell that is not sealed
        return;
      }
    }
    // Once we get to this point, we know all mines are sealed.
    // Hence, set game condition to WIN and expose any of the remaining cells.
    GetGame()->PlaySoundFromMap("win-sound.wav");
    GetGame()->SetGameState(Game::WIN);
    // Expose the rest of the cells
    for (auto row : mCellList)
    {
      for (auto cell : row)
      {
        if (cell->GetCellType() == UNEXPOSE)
        {
          Expose(cell);
        }
      }
    }
  }
}

void Grid::CheckAllCellsExposed()
{
  if (GetGame()->GetGameState() != Game::WIN)
  {
    for (auto& row : mCellList)
    {
      for (auto cell : row)
      {
        if (cell->GetCellType() == UNEXPOSE)
        {
          return;
        }
      }
    }
    // Once we get to this point, we know all cells are exposed.
    // Hence, set game condition to WIN
    GetGame()->PlaySoundFromMap("win-sound.wav");
    GetGame()->SetGameState(Game::WIN);
  }
}

void Grid::CheckForWin()
{
  // We win by either exposing all non-mine cells or sealing all mine cells
  CheckAllMinesSealed();
  CheckAllCellsExposed();
}
