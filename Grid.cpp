//
// Created by shehbaz on 12/10/2023.
//

#include "Grid.h"
#include "Game.h"
#include "Cell.h"

Grid::Grid(Game* game, int rows, int columns, int mines)
:Actor(game)
,mRows(rows)
,mColumns(columns)
,mMines(mines)
{
}

void Grid::Initialize()
{
//  mCellList.resize(mRows);
//  for (int i = 0; i < mRows; ++i)
//  {
//    mCellList[i].resize(mColumns);
//    for (int j = 0; j < mColumns; ++j)
//    {
//      Cell* cell = new Cell(GetGame(), this);
//    }
//  }
}
