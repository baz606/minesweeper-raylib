//
// Created by shehbaz on 12/6/2023.
//

#pragma once
#include "raylib.h"

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

  void GetInput();
  void UpdateGame();
  void GenerateOutput();

  bool isEnd;
};
