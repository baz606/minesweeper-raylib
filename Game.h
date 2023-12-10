//
// Created by shehbaz on 12/6/2023.
//

#pragma once

#include <vector>
#include <iostream>
#include <memory>

#include "raylib.h"

enum GameState
{
  INITIAL,
  PLAYING,
  WIN,
  GAME_OVER
};

// Forward declare Cell class
class Cell;

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

  GameState GetGetState() { return gameState; }

  bool ExitGame();
  void CloseGame();

  bool CanSeal();
  void Seal();
  void UnSeal();

private:
  const int SCREEN_WIDTH, SCREEN_HEIGHT;
  const char* title;
  // This rectangular plane is where cells will reside and drawn
  Rectangle plane;
  Font font;

  std::vector<std::vector<Cell*>> grid;
  std::vector<Cell*> mineCells;
  int rows;
  int columns;
  int totalMines;
  int totalSeals;
  GameState gameState;

  void ProcessInputs();
  void UpdateGame();
  void GenerateOutput();

  void DrawLogo();

  bool isEnd;

  void UnLoadData();

  void SetMineCells();

  void SetAdjacentCellsAround(Cell* cell);

  void GetAdjacentCellsFor(Cell* cell, std::vector<Cell*>& adjacentCells);

  void Expose(Cell* cell);

  void ShowAllMines();

  void HandleGameOver();

  void ResetGame();

  void CheckForWin();
};
