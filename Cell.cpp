//
// Created by shehbaz on 12/6/2023.
//

#include <string>
#include "Cell.h"

Cell::Cell()
:color(DARKGRAY)
,numOfMines(0)
,showNumOfMines(false)
,cellType(UNEXPOSE)
{
}

Cell::~Cell()
{
}

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
  switch (cellType)
  {
    case MINE:
      DrawRectangleRec(rectangle, color);
      break;
    case ADJACENT:
      DrawRectangleRec(rectangle, color);
      if (showNumOfMines)
      {
        DrawText(std::to_string(numOfMines).c_str(), screenPosition.x - 10, screenPosition.y - 15, 40, WHITE);
      }
      break;
    default:
      DrawRectangleRec(rectangle, color);
  }
  DrawRectangleLinesEx(rectangle, 3.0f, BLACK);
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

void Cell::SetShowNumOfMines(bool show)
{
  showNumOfMines = show;
}

void Cell::ResetVals()
{
  cellType = UNEXPOSE;
  color = DARKGRAY;
  numOfMines = 0;
  showNumOfMines = false;
}
