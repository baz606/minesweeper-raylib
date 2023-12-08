//
// Created by shehbaz on 12/6/2023.
//

#include "Game.h"

Game::Game(int screenWidth, int screenHeight, const char* title)
:SCREEN_WIDTH(screenWidth)
,SCREEN_HEIGHT(screenHeight)
,title(title)
{
  rows = 0;
  columns = 0;
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
  plane = { 0, 0, 900, 900 };
  rows = plane.width / Cell::LENGTH;
  columns = plane.height / Cell::LENGTH;
  float padding = 5.0f;

  grid.resize(rows);
  for (int i = 0; i < rows; i++)
  {
    grid[i].resize(columns);
    for (int j = 0; j < columns; j++)
    {
      Cell* cell = new Cell();
      cell->SetPosition(i, j);
      cell->SetRectangle(j * (Cell::LENGTH + padding), i * (Cell::LENGTH + padding), Cell::LENGTH, Cell::LENGTH);
      cell->SetCellType(UNEXPOSE);
      grid[i][j] = cell;
      printf("(%d,%d) ", cell->GetPosition()->x, cell->GetPosition()->y);
    }
    printf("\n");
  }

  SetMineCells();
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
  DrawFPS(SCREEN_WIDTH - 100, 20);
  // Draw a big/invisible rectangle where cells will reside
  DrawRectangleRec(plane, RAYWHITE);
  // Draw the grid cells
  for (auto& row : grid)
  {
    for (auto cell : row)
    {
      cell->Draw();
    }
  }
  //DrawText("Test Window", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 50, BLACK);
//  Rectangle rectangle = { 0, 0, 100, 100 };
//  DrawRectangleRec(rectangle, BLACK);
//  if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionRecs(grid, Rectangle(GetMouseX(), GetMouseY(), 0, 0)))
//  {
//    Rectangle rectangle1 = GetCollisionRec(grid, Rectangle(GetMouseX(), GetMouseY()));
//    printf("(%f, %f, %f, %f)\n", rectangle1.x, rectangle1.y, rectangle1.width, rectangle1.height);
//  }
  DrawLogo();
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
  UnLoadData();
  CloseWindow();
}

void Game::UnLoadData()
{
  // Deallocate memory of grid
  for (auto row : grid)
  {
    for (auto cell : row)
    {
      delete cell;
    }
    row.clear();
  }
  grid.clear();
}

void Game::DrawLogo()
{
  DrawText("@baz606", SCREEN_WIDTH - 300, SCREEN_HEIGHT / 2, 50, BLUE);
}

void Game::SetMineCells()
{
  totalMines = 9;
  int i = 0, j = 0, k = 0;
  SetRandomSeed(time(nullptr));
  while (k < totalMines)
  {
    i = GetRandomValue(0, rows - 1);
    j = GetRandomValue(0, columns - 1);
    // Set Mine cell
    grid[i][j]->SetCellType(MINE);
    // Set Adjacent cells around mine cell
    SetAdjacentCellsAround(grid[i][j]);
    k++;
  }
}

void Game::SetAdjacentCellsAround(Cell* cell)
{
  std::vector<Cell*> adjacentCells;
  GetAdjacentCellsFor(cell, adjacentCells);

  for (auto cell : adjacentCells)
  {
    if(cell->GetCellType() == UNEXPOSE)
    {
      cell->SetCellType(ADJACENT);
    }
  }
}

void Game::GetAdjacentCellsFor(Cell* cell, std::vector<Cell*>& adjacentCells)
{
  const int x = cell->GetPosition()->x;
  const int y = cell->GetPosition()->y;
  // Check top and bottom row
  for (int i = x - 1, z = x + 1, j = y - 1; j < y + 2; j++)
  {
    if (i >= 0 || z < rows)
    {
      if (i >= 0 && j >= 0 && j < columns)
      {
        // Valid adjacent cell
        adjacentCells.push_back(grid[i][j]);
      }
      if (z < rows && j >= 0 && j < columns)
      {
        // Valid adjacent cell
        adjacentCells.push_back(grid[z][j]);
      }

    }
    else
    {
      // No top or bottom row
      break;
    }
  }
  // Check left of the cell
  if ((y - 1) >= 0)
  {
    adjacentCells.push_back(grid[x][y - 1]);
  }
  // Check right of the cell
  if ((y + 1) < columns)
  {
    adjacentCells.push_back(grid[x][y + 1]);
  }
}
