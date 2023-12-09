//
// Created by shehbaz on 12/6/2023.
//

#include <string>
#include "Cell.h"

Cell::Cell()
: color(DARKGRAY)
, numOfMines(0)
, cellType(UNEXPOSE)
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
    case SEALED:
      color = GREEN;
      DrawRectangleRec(rectangle, color);
      break;
    case SEALED_MINE:
      color = PURPLE;
      DrawRectangleRec(rectangle, color);
      break;
    case EXPOSE:
      color = BLUE;
      DrawRectangleRec(rectangle, color);
      break;
    case ADJACENT_UNEXPOSE:
      color = DARKGRAY;
      DrawRectangleRec(rectangle, color);
      break;
    case ADJACENT:
      color = BLUE;
      DrawRectangleRec(rectangle, color);
      DrawText(std::to_string(numOfMines).c_str(), screenPosition.x - 10, screenPosition.y - 15, 40, WHITE);
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

void Cell::ResetVals()
{
  cellType = UNEXPOSE;
  color = DARKGRAY;
  numOfMines = 0;
  showAdjacent = false;
}

void Cell::ToggleSeal()
{
  // If sealing
  if (cellType == MINE)
  {
    cellType = SEALED_MINE;
    return;
  }
  else if (cellType == UNEXPOSE || cellType == ADJACENT_UNEXPOSE)
  {
    printf("SEALING UNEXPOSE OR ADJ UNEXPOSE");
    cellType = SEALED;
    return;
  }

  // If unsealing
  if (cellType == SEALED)
  {
    if (numOfMines > 0)
    {
      cellType = ADJACENT_UNEXPOSE;
    }
    else
    {
      cellType = UNEXPOSE;
    }
  }
  else if (cellType == SEALED_MINE)
  {
    cellType = MINE;

  }
  // Set cell color to DARKGRAY to show cell is unsealed
  color = DARKGRAY;
}
