//
// Created by shehbaz on 12/6/2023.
//

#pragma once

#include <vector>
#include <iostream>

#include "raylib.h"
#include "Cell.h"

/**
 * This Game class will be used to manage our game
 */
class Game
{
public:
  Game(int screenWidth, int screenHeight, const char* title);
  ~Game();

  void Initialize();

  void RunGame();

  bool ExitGame();
  void CloseGame();

private:
  const int SCREEN_WIDTH, SCREEN_HEIGHT;
  const char* title;
  // This plane is where cells will reside and drawn
  // This will help us with detecting collisions
  Rectangle plane;

  std::vector<std::vector<Cell*>> grid;
  int rows;
  int columns;
  int totalMines;

  void GetInput();
  void UpdateGame();
  void GenerateOutput();

  void DrawLogo();

  bool isEnd;

  void UnLoadData();

  void SetMineCells();

  void SetAdjacentCellsAround(Cell* cell);

  void GetAdjacentCellsFor(Cell* cell, std::vector<Cell*>& adjacentCells);
};
