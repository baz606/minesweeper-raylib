//
// Created by shehbaz on 12/10/2023.
//

#pragma once

#include <vector>
#include "Actor.h"

class Grid : public Actor
{
public:
  Grid(class Game* game, int rows, int columns, int mines);
  ~Grid() = default;

  void Initialize();
  void Reset();

  void UpdateActor(float deltaTime) override;
  void ProcessInput(int mouseX, int mouseY);

private:
  std::vector<std::vector<class Cell*>> mCellList;
  std::vector<class Cell*> mMineList;
  int mRows;
  int mColumns;
  int mMines;

  void SetMines();
//  void SetAdjacentCellsAround(Cell* cell);
//  void GetAdjacentCellsFor(Cell* cell, std::vector<class Cell*>& adjacentCells);
  void Expose(Cell* cell);
  int GetAdjacentCells(Cell* cell, std::vector<Cell*>& adjacentCells);
  void ToggleSeal(Cell *cell);

  void CheckForWin();
};
