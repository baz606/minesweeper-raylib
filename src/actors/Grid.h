//
// Created by shehbaz on 12/10/2023.
//

#pragma once

#include <vector>
#include "Actor.h"

class Grid : public Actor
{
public:
  Grid(class Game* game, Game::GameState gameState, int rows, int columns, int mines);
  ~Grid() = default;

  void Initialize();
  void Reset();

  void UpdateActor(float deltaTime) override;
  void ProcessInput(int mouseX, int mouseY);

  void SetMines();
  int GetMines() const { return mMines; }
  int GetTotalSeals() const { return mTotalSeals; }

private:
  std::vector<std::vector<class Cell*>> mCellList;
  std::vector<class Cell*> mMineList;
  int mRows;
  int mColumns;
  int mMines;
  int mTotalSeals;
//  void SetAdjacentCellsAround(Cell* cell);
//  void GetAdjacentCellsFor(Cell* cell, std::vector<class Cell*>& adjacentCells);
  void Expose(Cell* cell);
  int GetAdjacentCells(Cell* cell, std::vector<Cell*>& adjacentCells);
  void ToggleSeal(Cell *cell);

  void CheckForWin();
  void CheckAllMinesSealed();
  void CheckAllCellsExposed();

  // Secret feature related variables
  const float MAX_TIME = 1.0f; // seconds
  float currentTime; // seconds
  int bufferIndex;
  char buffer[6];
};
