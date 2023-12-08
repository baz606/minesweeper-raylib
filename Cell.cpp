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
  // This whole method will need to be re-written when I add the expose method
  if (cellType == MINE)
  {
    color = RED;
  }
  if (cellType == ADJACENT)
  {
    color = BLUE;
    DrawRectangleRec(rectangle, color);
    DrawRectangleLinesEx(rectangle, 2, BLACK);
    DrawText(std::to_string(numOfMines).c_str(), screenPosition.x - 10, screenPosition.y - 15, 40, WHITE);
    return;
  }
  DrawRectangleRec(rectangle, color);
  DrawRectangleLinesEx(rectangle, 2, BLACK);
}

void Cell::SetScreenPosition(int x, int y)
{
  screenPosition = { x, y };
}

void Cell::IncrementNumOfMines()
{
  numOfMines++;
}

void Cell::SetColor(Color color)
{
  this->color = color;
}
