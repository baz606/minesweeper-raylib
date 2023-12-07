//
// Created by shehbaz on 12/6/2023.
//

#include "Cell.h"

Cell::Cell()
:color(DARKGRAY)
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
  DrawRectangleRec(rectangle, color);
}
