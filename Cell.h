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

  Vector2Int* GetPosition() { return &position; }
  CellType GetCellType() { return cellType; }

  void Draw();

  // Length of this squared cell. Each cell will be the same length
  static const int LENGTH = 100;

private:
  // Index position in the 2D array of cells - easier to calculate adjacent cells
  Vector2Int position{};
  // The rectangle struct associated with this Cell that will be drawn on screen
  // Can be used to check for collision when a user selects this cell
  Rectangle rectangle{};
  // Color for this cell
  Color color;
  // Current state of the cell
  CellType cellType;
};
