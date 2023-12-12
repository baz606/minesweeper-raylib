//
// Created by shehbaz on 12/6/2023.
//

#pragma once

#include "Actor.h"

enum CellType
{
  UNEXPOSE,
  EXPOSE,
  ADJACENT,
  ADJACENT_UNEXPOSE,
  ADJACENT_SEALED,
  MINE,
  SEALED,
  SEALED_MINE
};

class Cell : public Actor
{
public:
  Cell(class Game* game, class Grid* grid);

  void UpdateActor(float deltaTime) override;

  // Getters/Setters
  void SetCellType(CellType cellType);
  [[nodiscard]] CellType GetCellType() const { return mCellType;}

  // Static cell length
  static const int LENGTH = 100;

private:
  CellType mCellType;
  class Grid* mGrid;
  // Number of mines around this cell, if adjacent to a mine
  int mNumOfMines;
};


//#include "raylib.h"
//
//struct Vector2Int
//{
//  int x;
//  int y;
//};
//
//enum CellType
//{
//  UNEXPOSE,
//  EXPOSE,
//  ADJACENT,
//  ADJACENT_UNEXPOSE,
//  MINE,
//  MINE_CROSS,
//  SEALED,
//  SEALED_MINE
//};
//
//class Cell
//{
//public:
//  Cell(class Game* game);
//  ~Cell();
//
//  void SetPosition(int x, int y);
//  void SetRectangle(float x, float y, float width, float height);
//  void SetCellType(CellType cellType) { this->cellType = cellType; }
//  void SetScreenPosition(int x, int y);
//  void SetColor(Color color);
//
//  const Vector2Int* GetPosition() { return &position; }
//  const Vector2Int* GetScreenPosition() { return &screenPosition; };
//  CellType GetCellType() { return cellType; }
//
//  void Draw();
//  void IncrementNumOfMines();
//
//  // Length of this squared cell. Each cell will be the same length
//  static const int LENGTH = 100;
//
//  void ResetVals();
//
//  void ToggleSeal();
//
//private:
//  // Screen position, i.e. coordinates for this Cell
//  Vector2Int screenPosition;
//  // Index position in the 2D array of cells - easier to calculate adjacent cells
//  Vector2Int position;
//  // The rectangle struct associated with this Cell that will be drawn on screen
//  // Can be used to check for collision when a user selects this cell
//  Rectangle rectangle;
//  // Color for this cell
//  Color color;
//  // Current state of the cell
//  CellType cellType;
//  // Number of mines around this cell
//  int numOfMines;
//  // Handle to the game manager
//  class Game* game;
//
//  void DrawCross() const;
//};
