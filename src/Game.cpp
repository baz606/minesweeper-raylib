//
// Created by shehbaz on 12/6/2023.
//

#include <algorithm>

#include "Game.h"
#include "Grid.h"
#include "Cell.h"
#include "DrawComponent.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

Game::Game(int screenWidth, int screenHeight, const char *title)
:mScreenWidth(screenWidth)
,mScreenHeight(screenHeight)
,mTitle(title)
,mIsRunning(true)
,mGameState(SPLASH_SCREEN)
,mGrid(nullptr)
{
}

void Game::Initialize()
{
  InitWindow(mScreenWidth, mScreenHeight, mTitle);
  SetTargetFPS(60);
  SetExitKey(KEY_NULL);

  // Load font
  mFont = LoadFontEx("./resources/lets-eat.ttf", 200, nullptr, 0);

  // Initialize the grid with rows x columns cells
  mGrid = new Grid(this, 9, 9, 9);
  mGrid->Initialize();

}

void Game::RunGame()
{
  ProcessInput();
  UpdateGame();
  GenerateOutput();
}

void Game::ProcessInput()
{
  if (mGameState == SPLASH_SCREEN)
  {
    if (GetKeyPressed() > 0)
    {
      mGameState = MENU;
    }
  }
  else if (mGameState == PLAYING)
  {
    mGrid->ProcessInput(GetMouseX(), GetMouseY());
    // Reset game at anytime in PLAYING state by pressing R key
    if (IsKeyReleased(KEY_R))
    {
      mGrid->Reset();
    }
  }
  else if (mGameState == WIN || mGameState == GAME_OVER)
  {
    if (IsKeyReleased(KEY_SPACE))
    {
      mGrid->Reset();
    }
  }
}

void Game::UpdateGame()
{
  for (auto actor : mActors)
  {
    actor->Update(GetFrameTime());
  }
}

void Game::GenerateOutput()
{
  BeginDrawing();
  // Display menu screen according to game state
  switch (mGameState)
  {
    case SPLASH_SCREEN:
    {
      ClearBackground(LIGHTGRAY);
      Vector2 pixelLength = MeasureTextEx(mFont, "@baz606", 200, 0);
      Vector2 pos = { mScreenWidth / 2.f, mScreenHeight / 2.f};
      float rotation = 0.f;
      DrawTextPro(mFont, "@baz606", pos, { pixelLength.x / 2, pixelLength.y / 2 }, rotation, 200, 0, VIOLET);

    }
    break;
    case MENU:
    {
      ClearBackground(DARKGRAY);
      float buttonWidth = 300.f, buttonHeight = 100.f;
      float padding = 75.f;
      GuiSetStyle(DEFAULT, TEXT_SIZE, 40);
      GuiSetStyle(DEFAULT, TEXT_SPACING, 10);
      GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0x000000FF);
      if (GuiButton({(mScreenWidth / 2.f) - (buttonWidth / 2.f),
                     (mScreenHeight / 2.f) - (buttonHeight / 2.f) - padding,
                     buttonWidth,
                     buttonHeight},
                    "START"))
      {
        printf("START GAME!\n");
        mGameState = PLAYING;
      }
      if (GuiButton({(mScreenWidth / 2.f) - (buttonWidth / 2.f),
                     (mScreenHeight / 2.f) - (buttonHeight / 2.f) + buttonHeight,
                     buttonWidth,
                     buttonHeight},
                    "EXIT"))
      {
        printf("EXIT GAME!\n");
        mIsRunning = false;
      }
    }
    break;
    default:
    {
      // This is our default PLAYING rendering output
      // This way we can render our GAME_OVER rectangular box correctly
      ClearBackground(LIGHTGRAY);
      DrawTextEx(mFont,
                 std::string("MINES: " + std::to_string(mGrid->GetTotalSeals())).c_str(),
                 { (float)mScreenWidth - 300, 100 },
                 90, 0, RED);

      Vector2 pixelLength = MeasureTextEx(mFont, "@baz606", 100, 0);
      Vector2 final = { (float)mScreenWidth - 320 + (pixelLength.x / 2), ((float)mScreenHeight / 2 ) + (pixelLength.y / 2) };
      DrawTextPro(mFont, "@baz606", final, { pixelLength.x / 2, pixelLength.y / 2 }, 0.f, 100, 0, VIOLET);

      for (auto drawCom: mDraws)
      {
        drawCom->Draw();
      }

      if (mGameState == GAME_OVER)
      {
        int fontSize = 50;
        int width = 1200, height = 500;
        DrawRectangle((mScreenWidth / 2) - (width / 2), (mScreenHeight / 2) - (height / 2), width, height, {0, 0, 0, 220});
        DrawText("YOU CLICKED A MINE CELL! GAME OVER!", (mScreenWidth / 2) - 500, (mScreenHeight / 2) - 40, fontSize, RED);
        DrawText("PRESS SPACE BAR TO TRY AGAIN!", (mScreenWidth / 2) - 500, (mScreenHeight / 2) + 20, fontSize, RED);
      }
      else if (mGameState == WIN)
      {
        int width = 1200, height = 500;
        int fontSize = 50;
        DrawRectangle((mScreenWidth / 2) - (width / 2), (mScreenHeight / 2) - (height / 2), width, height, {0, 0, 0, 220});
        DrawText("CONGRATULATIONS, YOU HAVE WON!", (mScreenWidth / 2) - 500, (mScreenHeight / 2) - 40, fontSize, GREEN);
        DrawText("PRESS SPACE BAR TO PLAY AGAIN!", (mScreenWidth / 2) - 500, (mScreenHeight / 2) + 20, fontSize, GREEN);
      }
    }
    break;
  }
  EndDrawing();
}

void Game::AddActor(Actor *actor)
{
  mActors.emplace_back(actor);
}

void Game::RemoveActor(Actor *actor)
{
  auto iter = std::find(mActors.begin(), mActors.end(), actor);
  if (iter != mActors.end())
  {
    mActors.erase(iter);
  }
}

void Game::AddDraw(class DrawComponent *mesh)
{
  int myDrawOrder = mesh->GetDrawOrder();
  auto iter = mDraws.begin();
  for (; iter != mDraws.end(); ++iter)
  {
    if (myDrawOrder < (*iter)->GetDrawOrder())
    {
      break;
    }
  }
  mDraws.insert(iter, mesh);
}

void Game::RemoveDraw(class DrawComponent *mesh)
{
  auto iter = std::find(mDraws.begin(), mDraws.end(), mesh);
  if (iter != mDraws.end())
  {
    mDraws.erase(iter);
  }
}

bool Game::IsRunning() const
{
  return (!WindowShouldClose() && mIsRunning);
}

void Game::Shutdown()
{
  UnloadData();
  UnloadFont(mFont);
  CloseWindow();
}

void Game::UnloadData()
{
  while (!mActors.empty())
  {
    delete mActors.back();
  }
}

//
//Game::Game(int screenWidth, int screenHeight, const char* title)
//:SCREEN_WIDTH(screenWidth)
//,SCREEN_HEIGHT(screenHeight)
//{
//  this->title = title;
//  mIsRunning = true;
//  rows = 0;
//  columns = 0;
//}
//
//Game::~Game()
//{
//}
//
//void Game::Initialize()
//{
//  // Game initialization
//  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, title);
//  SetTargetFPS(60);
//  // Set up grid so it can be draw
//  plane = { 0, 0, 910, 910 };
//  rows = 9;
//  columns = 9;
//  int padding = 0;
//
//  grid.resize(rows);
//  for (int i = 0; i < rows; i++)
//  {
//    grid[i].resize(columns);
//    for (int j = 0; j < columns; j++)
//    {
//      Cell* cell = new Cell(this);
//      cell->SetPosition(i, j);
//      cell->SetRectangle(j * (Cell::LENGTH + padding), i * (Cell::LENGTH + padding), Cell::LENGTH, Cell::LENGTH);
//      cell->SetScreenPosition((j * (Cell::LENGTH + padding)) + (Cell::LENGTH / 2), (i * (Cell::LENGTH + padding)) + (Cell::LENGTH / 2));
//      cell->SetCellType(UNEXPOSE);
//      grid[i][j] = cell;
//      printf("(%d,%d) ", cell->GetScreenPosition()->x, cell->GetScreenPosition()->y);
//    }
//    printf("\n");
//  }
//  SetMineCells();
//  // Load logo font
//  font = LoadFontEx("./resources/lets-eat.ttf", 200, nullptr, 0);
//  // Logo
//  pixelLength = MeasureTextEx(font, "@baz606", 100, 0);
////  DrawTextPro(font, "@baz606", { (float)SCREEN_WIDTH - 320 + (pixelLength.x / 2), ((float)SCREEN_HEIGHT / 2 ) + (pixelLength.y / 2)},
////              { pixelLength.x / 2, pixelLength.y / 2 }, rotation, 100, 0, VIOLET);
//  initial = { (float)SCREEN_WIDTH - 320 + (pixelLength.x / 2), pixelLength.y };
//  final = { (float)SCREEN_WIDTH - 320 + (pixelLength.x / 2), ((float)SCREEN_HEIGHT / 2 ) + (pixelLength.y / 2) };
//  textAnimation = TextAnimation(-20.f, false, 200);
//  textAnimation1 = TextAnimation(20, true, 50);
//  textAnimation2 = TextAnimation(0, false, 20);
//
//  gameState = PLAYING;
//}
//
//void Game::ResetGame()
//{
//  // Reset position and animation of logo
//  initial = { (float)SCREEN_WIDTH - 320 + (pixelLength.x / 2), pixelLength.y };
//  final = { (float)SCREEN_WIDTH - 320 + (pixelLength.x / 2), ((float)SCREEN_HEIGHT / 2 ) + (pixelLength.y / 2) };
//  textAnimation.Reset();
//  textAnimation1.Reset();
//  textAnimation2.Reset();
//
//  for (auto& row : grid)
//  {
//    for (auto cell : row)
//    {
//      cell->ResetVals();
//    }
//  }
//  SetMineCells();
//  gameState = PLAYING;
//}
//
//void Game::RunGame()
//{
//  ProcessInput();
//  UpdateGame();
//  GenerateOutput();
//}
//
//void Game::ProcessInput()
//{
//  // Get player input
//  if (gameState == PLAYING)
//  {
//    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
//    {
//      // Check which cell the user selected
//      int i = std::lround(GetMouseY() / Cell::LENGTH);
//      int j = std::lround(GetMouseX() / Cell::LENGTH);
//      if (i >= 0 && i < rows && j >= 0 && j < columns)
//      {
//        Expose(grid[i][j]);
//      }
//    }
//    else if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
//    {
//      // Check which cell the user selected to seal
//      int i = std::lround(GetMouseY() / Cell::LENGTH);
//      int j = std::lround(GetMouseX() / Cell::LENGTH);
//      if (i >= 0 && i < rows && j >= 0 && j < columns)
//      {
//        grid[i][j]->ToggleSeal();
//      }
//    }
//  }
//  else if (IsKeyReleased(KEY_SPACE) && (gameState == GAME_OVER || gameState == WIN))
//  {
//    gameState = INITIAL;
//  }
//  // Pressing R at anytime resets the grid
//  if (IsKeyReleased(KEY_R))
//  {
//    gameState = INITIAL;
//  }
//}
//
//void Game::UpdateGame()
//{
//  if (gameState == INITIAL)
//  {
//    ResetGame();
//  }
//  else if (gameState == GAME_OVER)
//  {
//    HandleGameOver();
//  }
//  CheckForWin();
//}
//
//void Game::GenerateOutput()
//{
//  BeginDrawing();
//  ClearBackground(LIGHTGRAY);
//  DrawFPS(SCREEN_WIDTH - 100, 20);
//  DrawLogo();
//  DrawTextEx(font, std::string("MINES: " + std::to_string(totalSeals)).c_str(), { (float)SCREEN_WIDTH - 300, 100 }, 90, 0, RED);
//  // Draw a big/invisible rectangle where cells will reside
//  DrawRectangleRec(plane, RAYWHITE);
//  // Draw the grid cells
//  for (auto& row : grid)
//  {
//    for (auto cell : row)
//    {
//      cell->Draw();
//    }
//  }
//  if (gameState == GAME_OVER)
//  {
//    int width = 1200, height = 500;
//    int fontSize = 50;
//    DrawRectangle((SCREEN_WIDTH / 2) - (width / 2), (SCREEN_HEIGHT / 2) - (height / 2), width, height, {0, 0, 0, 220});
//    DrawText("YOU CLICKED A MINE CELL! GAME OVER!", (SCREEN_WIDTH / 2) - 500, (SCREEN_HEIGHT / 2) - 40, fontSize, RED);
//    DrawText("PRESS SPACE BAR TO TRY AGAIN!", (SCREEN_WIDTH / 2) - 500, (SCREEN_HEIGHT / 2) + 20, fontSize, RED);
//  }
//  else if (gameState == WIN)
//  {
//    int width = 1200, height = 500;
//    int fontSize = 50;
//    DrawRectangle((SCREEN_WIDTH / 2) - (width / 2), (SCREEN_HEIGHT / 2) - (height / 2), width, height, {0, 0, 0, 220});
//    DrawText("CONGRATULATIONS, YOU HAVE WON!", (SCREEN_WIDTH / 2) - 500, (SCREEN_HEIGHT / 2) - 40, fontSize, GREEN);
//    DrawText("PRESS SPACE BAR TO PLAY AGAIN!", (SCREEN_WIDTH / 2) - 500, (SCREEN_HEIGHT / 2) + 20, fontSize, GREEN);
//  }
//  EndDrawing();
//}
//
//void Game::DrawLogo()
//{
//  if (!IsMouseButtonDown(MOUSE_MIDDLE_BUTTON))
//  {
//    //rotation = 50;
//    speed = 50;
//  }
//  else
//  {
//    speed = 0;
//  }
//  speed = 2000;
////  rotation += speed * GetFrameTime();
//  //  Vector2 pixelLength = MeasureTextEx(font, "@baz606", 100, 0);
//  //  DrawTextEx(font, "@baz606", { (float)SCREEN_WIDTH - 320, (float)SCREEN_HEIGHT / 2 }, 100, 0, VIOLET);
//
//  if (initial.y < final.y)
//  {
//    rotation = 20;
//    DrawTextPro(font, "@baz606", initial,
//                { pixelLength.x / 2, pixelLength.y / 2 }, rotation, 100, 0, VIOLET);
//    initial.y += speed * GetFrameTime();
//    // initial and final are not equal
//  }
//  else
//  {
//    if (textAnimation.Animate(&rotation))
//    {
//      if (textAnimation1.Animate(&rotation))
//      {
//        textAnimation2.Animate(&rotation);
//      }
//    }
//    DrawTextPro(font, "@baz606", final, { pixelLength.x / 2, pixelLength.y / 2 }, rotation, 100, 0, VIOLET);
//  }
//
//}
//
//void Game::SetMineCells()
//{
//  totalMines = 9;
//  totalSeals = totalMines;
//  int i = 0, j = 0, k = 0;
//  SetRandomSeed(time(nullptr));
//  mineCells.clear();
//  while (k < totalMines)
//  {
//    i = GetRandomValue(0, rows - 1);
//    j = GetRandomValue(0, columns - 1);
//    // Set Mine cell
//    if (grid[i][j]->GetCellType() == UNEXPOSE)
//    {
//      grid[i][j]->SetCellType(MINE);
//      mineCells.push_back(grid[i][j]);
//    }
//    else
//    {
//      // This randomly selected cell is either a MINE or ADJACENT cell already
//      continue;
//    }
//    k++;
//  }
//
//  for (auto cell : mineCells)
//  {
//    // Set adjacent cells around this mine cell
//    SetAdjacentCellsAround(cell);
//  }
//}
//
//void Game::SetAdjacentCellsAround(Cell* cell)
//{
//  std::vector<Cell*> adjacentCells;
//  GetAdjacentCellsFor(cell, adjacentCells);
//
//  for (auto adjCell : adjacentCells)
//  {
//    if(adjCell->GetCellType() != MINE)
//    {
//      // If not a mine cell, set adjacent cell type and increment the number of mines around it
//      adjCell->SetCellType(ADJACENT_UNEXPOSE);
//      adjCell->IncrementNumOfMines();
//    }
//  }
//}
//
//void Game::GetAdjacentCellsFor(Cell* cell, std::vector<Cell*>& adjacentCells)
//{
//  const int x = cell->GetPosition()->x;
//  const int y = cell->GetPosition()->y;
//  // Check top and bottom row
//  for (int i = x - 1, z = x + 1, j = y - 1; j < y + 2; j++)
//  {
//    if (i >= 0 || z < rows)
//    {
//      if (i >= 0 && j >= 0 && j < columns)
//      {
//        // Valid adjacent cell
//        adjacentCells.push_back(grid[i][j]);
//      }
//      if (z < rows && j >= 0 && j < columns)
//      {
//        // Valid adjacent cell
//        adjacentCells.push_back(grid[z][j]);
//      }
//    }
//    else
//    {
//      // No top or bottom row
//      break;
//    }
//  }
//  // Check left of the cell
//  if ((y - 1) >= 0)
//  {
//    adjacentCells.push_back(grid[x][y - 1]);
//  }
//  // Check right of the cell
//  if ((y + 1) < columns)
//  {
//    adjacentCells.push_back(grid[x][y + 1]);
//  }
//}
//
//void Game::Expose(Cell *cell)
//{
//  if (cell->GetCellType() == MINE)
//  {
//    gameState = GAME_OVER;
//  }
//  else if (cell->GetCellType() == ADJACENT_UNEXPOSE)
//  {
//    cell->SetCellType(ADJACENT);
//  }
//  else if (cell->GetCellType() == UNEXPOSE)
//  {
//    cell->SetCellType(EXPOSE);
//    // Get adjacent cells and recursively call expose
//    std::vector<Cell*> adjacentCells;
//    GetAdjacentCellsFor(cell, adjacentCells);
//    for (auto adjCell : adjacentCells)
//    {
//      if (adjCell->GetCellType() != MINE)
//      {
//        this->Expose(adjCell);
//      }
//    }
//  }
//}
//
//void Game::ShowAllMines()
//{
//  for (auto cell : mineCells)
//  {
//    if (cell->GetCellType() == SEALED_MINE)
//    {
//      cell->SetCellType(MINE_CROSS);
//    }
//    else if (cell->GetCellType() != MINE_CROSS)
//    {
//      cell->SetCellType(MINE);
//    }
//    cell->SetColor(RED);
//  }
//}
//
//void Game::HandleGameOver()
//{
//  ShowAllMines();
//}
//
//void Game::CheckForWin()
//{
//  for (auto mine : mineCells)
//  {
//    if (mine->GetCellType() == MINE)
//    {
//      // There is at least one mine cell not sealed
//      return;
//    }
//  }
//  gameState = WIN;
//}
//
//bool Game::CanSeal()
//{
//  return totalSeals > 0;
//}
//
//void Game::Seal()
//{
//  totalSeals--;
//}
//
//void Game::UnSeal()
//{
//  totalSeals++;
//}
//
//bool Game::IsRunning()
//{
//  // Right now the only way to end the game is closing the window or pressing escape key
//  // Later, we can add other ways to exit out of the game
//  mIsRunning = !WindowShouldClose();
//  return mIsRunning;
//}
//
//void Game::Shutdown()
//{
//  UnLoadData();
//  CloseWindow();
//}
//
//void Game::UnLoadData()
//{
//  // Deallocate memory of grid
//  for (auto& row : grid)
//  {
//    for (auto cell : row)
//    {
//      delete cell;
//    }
//    row.clear();
//  }
//  grid.clear();
//  mineCells.clear();
//  UnloadFont(font);
//}
//
//Game::TextAnimation::TextAnimation(float targetRotation, bool isClockwise, float speed)
//{
//  this->targetRotation = targetRotation;
//  this->isClockwise = isClockwise;
//  isFinished = false;
//  this->speed = speed;
//}
//
//bool Game::TextAnimation::Animate(float *currentRotation)
//{
//  if (!isFinished)
//  {
//    if (isClockwise)
//    {
//      if ((*currentRotation) < targetRotation)
//      {
//        // Animate to targetRotation
//        (*currentRotation) += speed * GetFrameTime();
//        // Check if rotation goes over targetRotation
//        if((*currentRotation) > targetRotation)
//        {
//          (*currentRotation) = targetRotation;
//        }
//      }
//      else
//      {
//        isFinished = true;
//        return isFinished;
//      }
//    }
//    else
//    {
//      if ((*currentRotation) > targetRotation)
//      {
//        // Animate to targetRotation
//        (*currentRotation) -= speed * GetFrameTime();
//        // Check if rotation goes under targetRotation
//        if((*currentRotation) < targetRotation)
//        {
//          (*currentRotation) = targetRotation;
//        }
//      }
//      else
//      {
//        isFinished = true;
//        return isFinished;
//      }
//    }
//  }
//  return isFinished;
//}
//
//void Game::TextAnimation::Reset()
//{
//  isFinished = false;
//}
