//
// Created by shehbaz on 12/6/2023.
//

//#include <string>
#include "Cell.h"
#include "Game.h"
#include "Grid.h"

Cell::Cell(Game *game, Grid *grid)
        : Actor(game)
        ,mGrid(grid)
{
}

void Cell::UpdateActor(float deltaTime)
{
}


//
//Cell::Cell(Game* game)
//:color(DARKGRAY)
//,numOfMines(0)
//,cellType(UNEXPOSE)
//,screenPosition(0, 0)
//,position(0, 0)
//,rectangle(0, 0, 0, 0)
//{
//  this->game = game;
//}
//
//Cell::~Cell()
//{
//}
//
//void Cell::SetPosition(int x, int y)
//{
//  position = { x, y };
//}
//
//void Cell::SetRectangle(float x, float y, float width, float height)
//{
//  rectangle = { x, y, width, height };
//}
//
//void Cell::Draw()
//{
//  // This whole method will need to be re-written when I add the expose method
//  switch (cellType)
//  {
//    case SEALED:
//    case SEALED_MINE:
//      color = PURPLE;
//      DrawRectangleRec(rectangle, color);
//      DrawCross();
//      break;
//    case MINE_CROSS:
//      DrawRectangleRec(rectangle, color);
//      DrawCross();
//      break;
//    case EXPOSE:
//      color = BLUE;
//      DrawRectangleRec(rectangle, color);
//      break;
//    case ADJACENT_UNEXPOSE:
//      color = DARKGRAY;
//      DrawRectangleRec(rectangle, color);
//      break;
//    case ADJACENT:
//      color = BLUE;
//      DrawRectangleRec(rectangle, color);
//      DrawText(std::to_string(numOfMines).c_str(), screenPosition.x - 10, screenPosition.y - 15, 40, WHITE);
//      break;
//    default:
//      DrawRectangleRec(rectangle, color);
//  }
//  DrawRectangleLinesEx(rectangle, 3.0f, BLACK);
//}
//
//void Cell::DrawCross() const
//{
//  DrawLineEx({rectangle.x, rectangle.y }, {rectangle.x + LENGTH, rectangle.y + LENGTH }, 5, BLACK);
//  DrawLineEx({rectangle.x + LENGTH, rectangle.y }, {rectangle.x, rectangle.y + LENGTH }, 5, BLACK);
//}
//
//void Cell::SetScreenPosition(int x, int y)
//{
//  screenPosition = { x, y };
//}
//
//void Cell::IncrementNumOfMines()
//{
//  numOfMines++;
//}
//
//void Cell::SetColor(Color color)
//{
//  this->color = color;
//}
//
//void Cell::ResetVals()
//{
//  cellType = UNEXPOSE;
//  color = DARKGRAY;
//  numOfMines = 0;
//}
//
//void Cell::ToggleSeal()
//{
//  // If sealing
//  if (cellType == MINE && game->CanSeal())
//  {
//    cellType = SEALED_MINE;
//    game->Seal();
//    return;
//  }
//  else if ((cellType == UNEXPOSE || cellType == ADJACENT_UNEXPOSE) && game->CanSeal())
//  {
//    cellType = SEALED;
//    game->Seal();
//    return;
//  }
//
//  // If unsealing
//  if (cellType == SEALED)
//  {
//    if (numOfMines > 0)
//    {
//      cellType = ADJACENT_UNEXPOSE;
//    }
//    else
//    {
//      cellType = UNEXPOSE;
//    }
//    color = DARKGRAY;
//    game->UnSeal();
//  }
//  else if (cellType == SEALED_MINE)
//  {
//    cellType = MINE;
//    color = DARKGRAY;
//    game->UnSeal();
//  }
//}
