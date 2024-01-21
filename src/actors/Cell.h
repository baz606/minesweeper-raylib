//
// Created by shehbaz on 12/6/2023.
//

#pragma once

#include "Actor.h"

struct Vector2Int
{
  int x;
  int y;
};

enum CellType
{
  UNEXPOSE,
  EXPOSE,
  ADJACENT,
  MINE,
  MINE_SEALED,
  MINE_EXPOSE,
  SEALED
};

class Cell : public Actor
{
public:
  Cell(class Game* game, Game::GameState gameState, class Grid* grid);

  void SetupComponents();
  void UpdateActor(float deltaTime) override;

  // Getters/Setters
  void SetCellType(CellType cellType);
  void SetIndex(int x, int y);
  [[nodiscard]] CellType GetCellType() const { return mCellType;}
  [[nodiscard]] int GetNumOfMines() const { return mNumOfMines; }
  void SetNumOfMines(int numOfMines) { mNumOfMines = numOfMines; }
  [[nodiscard]] const Vector2Int& GetIndex() const { return mIndex; }

  // Static cell length
  static const int LENGTH = 100;

  void Reset();

private:
  CellType mCellType;
  class Grid* mGrid;
  Vector2Int mIndex;
  // Number of mines around this cell, if adjacent to a mine
  int mNumOfMines;
};