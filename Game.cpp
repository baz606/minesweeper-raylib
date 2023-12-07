//
// Created by shehbaz on 12/6/2023.
//

#include "Game.h"

Game::Game(int screenWidth, int screenHeight, const char* title)
:SCREEN_WIDTH(screenWidth)
,SCREEN_HEIGHT(screenHeight)
,title(title)
{
  plane = { 0, 0, 900, 900 };
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

  // Set up grid so it can be draw
  rows = 9; columns = 9;
//  for (int i = 0; i < rows; i++)
//  {
//    for (int j = 0; j < columns; j++)
//    {
//      Cell* cell = new Cell();
//      cell->SetPosition(i, j);
//    }
//  }
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
  // Draw a big/invisible rectangle where cells will reside
  DrawRectangleRec(plane, RAYWHITE);
  //DrawText("Test Window", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 50, BLACK);
//  Rectangle rectangle = { 0, 0, 100, 100 };
//  DrawRectangleRec(rectangle, BLACK);
//  if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionRecs(grid, Rectangle(GetMouseX(), GetMouseY(), 0, 0)))
//  {
//    Rectangle rectangle1 = GetCollisionRec(grid, Rectangle(GetMouseX(), GetMouseY()));
//    printf("(%f, %f, %f, %f)\n", rectangle1.x, rectangle1.y, rectangle1.width, rectangle1.height);
//  }
  DrawFPS(SCREEN_WIDTH - 100, 20);
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
