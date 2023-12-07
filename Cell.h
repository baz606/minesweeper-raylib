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

class Cell
{
public:
  Cell();
  ~Cell();

  Vector2Int* GetPosition() { return &position; }
  Rectangle* GetRectangle() { return &rectangle; }
  void SetPosition(int x, int y);
  void SetRectangle(float x, float y, float width, float height);


private:
  // Index position in the 2D array of cells - easier to calculate adjacent cells
  Vector2Int position;
  // The rectangle struct associated with this Cell that will be drawn on screen
  // Can be used to check for collision when a user selects this cell
  Rectangle rectangle;
  // Length of this squared cell -> This cell will be length x length
  float length;
};
