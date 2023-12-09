//
// Created by shehbaz on 12/6/2023.
//

#pragma once

#include "raylib.h"

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
  MINE
};

class Cell
{
public:
  Cell();
  ~Cell();

  void SetPosition(int x, int y);
  void SetRectangle(float x, float y, float width, float height);
  void SetCellType(CellType cellType) { this->cellType = cellType; }
  void SetScreenPosition(int x, int y);
  void SetColor(Color color);

  const Vector2Int* GetPosition() { return &position; }
  const Vector2Int* GetScreenPosition() { return &screenPosition; };
  CellType GetCellType() { return cellType; }

  void Draw();
  void IncrementNumOfMines();

  // Length of this squared cell. Each cell will be the same length
  static const int LENGTH = 100;

  void SetShowNumOfMines(bool show);

  void ResetVals();

private:
  // Screen position, i.e. coordinates for this Cell
  Vector2Int screenPosition;
  // Index position in the 2D array of cells - easier to calculate adjacent cells
  Vector2Int position;
  // The rectangle struct associated with this Cell that will be drawn on screen
  // Can be used to check for collision when a user selects this cell
  Rectangle rectangle;
  // Color for this cell
  Color color;
  // Current state of the cell
  CellType cellType;
  // Number of mines around this cell
  int numOfMines;
  // Whether to show number of mines on a cell
  bool showNumOfMines;
};
