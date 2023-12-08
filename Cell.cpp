//
// Created by shehbaz on 12/6/2023.
//

#include <string>
#include "Cell.h"

Cell::Cell()
:color(DARKGRAY)
,numOfMines(0)
{
}

Cell::~Cell() = default;

void Cell::SetPosition(int x, int y)
{
  position = { x, y };
}

void Cell::SetRectangle(float x, float y, float width, float height)
{
  rectangle = { x, y, width, height };
}

void Cell::Draw()
{
  if (cellType == MINE)
  {
    color = RED;
  }
  if (cellType == ADJACENT)
  {
    color = BLUE;
    DrawRectangleRec(rectangle, color);
    DrawText(std::to_string(numOfMines).c_str(), screenPosition.x - 10, screenPosition.y - 15, 40, WHITE);
    return;
  }
  DrawRectangleRec(rectangle, color);
}

void Cell::SetScreenPosition(float x, float y)
{
  screenPosition = { x, y };
}

void Cell::IncrementNumOfMines()
{
  numOfMines++;
}
