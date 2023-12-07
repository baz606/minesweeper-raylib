//
// Created by shehbaz on 12/6/2023.
//

#include "Game.h"

Game::Game(int screenWidth, int screenHeight, const char* title)
:SCREEN_WIDTH(screenWidth)
,SCREEN_HEIGHT(screenHeight)
,title(title)
{
}

Game::~Game()
{
}

void Game::Initialize()
{
  // Game initialization
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, title);
  SetTargetFPS(60);
  isEnd = false;
}

void Game::RunGame()
{
  GetInput();
  UpdateGame();
  GenerateOutput();
}

void Game::GetInput()
{
  // Get player input
}

void Game::UpdateGame()
{
  // Update game world
}

void Game::GenerateOutput()
{
  // Render/Draw graphics
  BeginDrawing();
  ClearBackground(RAYWHITE);
  DrawText("Test Window", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 50, BLACK);
  EndDrawing();
}

bool Game::ExitGame()
{
  // Right now the only way to end the game is closing the window or pressing escape key
  // Later, we can add other ways to exit out of the game
  isEnd = WindowShouldClose();
  return isEnd;
}

void Game::CloseGame()
{
  CloseWindow();
}
