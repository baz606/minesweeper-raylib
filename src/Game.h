//
// Created by shehbaz on 12/6/2023.
//

#pragma once

#include <vector>
#include "raylib.h"

class Game
{
public:
  enum GameState
  {
    INITIAL,
    PLAYING,
    WIN,
    GAME_OVER
  };

  Game(int screenWidth, int screenHeight, const char *title);
  ~Game() = default;

  // Methods to run our game loop
  void Initialize();
  void RunGame();
  void Shutdown();

  // Add/Remove actors from the game
  void AddActor(class Actor* actor);
  void RemoveActor(class Actor* actor);

  // Add/Remove Mesh components
  void AddDraw(class DrawComponent *mesh);
  void RemoveDraw(class DrawComponent *mesh);

  // Set/Get Game state
  void SetGameState(GameState gameState) { mGameState = gameState; }
  [[nodiscard]] GameState GetGameState() const { return mGameState; }

//  void AddFont(class Font* font);
//  void RemoveFont(class Font* font);

  // Check if the game window is running
  [[nodiscard]] bool IsRunning() const;

private:
  // Game window specific
  int mScreenWidth, mScreenHeight;
  const char* mTitle;

  // Main game loop
  void ProcessInput();
  void UpdateGame();
  void GenerateOutput();

  // Deallocate any memory on the heap
  void UnloadData();

  // Handle game conditions
//  void HandleGameOver();
//  void ResetGame();
//  void CheckForWin();

  // Current game state and end conditions
  GameState mGameState;
  bool mIsRunning;

  // All the actors in the game
  std::vector<class Actor*> mActors;
  // All Cell meshes in the game
  std::vector<class DrawComponent*> mDraws;

  // Game Specific
  // This mGrid contains all cells
  class Grid* mGrid;
};

//#include <vector>
//#include <iostream>
//#include <memory>
//
//#include "raylib.h"
//
//// Forward declare Cell class
//class Cell;
//
///**
// * This Game class will be used to manage our game
// */
//class Game
//{
//public:
//  Game(int screenWidth, int screenHeight, const char* title);
//  ~Game();
//
//  enum GameState
//  {
//    INITIAL,
//    PLAYING,
//    WIN,
//    GAME_OVER
//  };
//
//  void Initialize();
//  void RunGame();
//  void Shutdown();
//  bool IsRunning();
//
//  // Move this section to the cell class?
////  bool CanSeal();
////  void Seal();
////  void UnSeal();
//
//private:
//  // Game window specific
//  int SCREEN_WIDTH, SCREEN_HEIGHT;
//  const char* title;
//
//  // Main game loop
//  void ProcessInput();
//  void UpdateGame();
//  void GenerateOutput();
//
//  // Handle game conditions
//  void HandleGameOver();
//  void ResetGame();
//  void CheckForWin();
//
//  // Deallocate any memory on the heap
//  void UnLoadData();
//
//  // Current game state and end conditions
//  GameState gameState;
//  bool mIsRunning;
//
//  // All the actors in the game
//  std::vector<class Actor*> mActors;
//
//  // Game Specific
//  // This mGrid contains all cells
//  class Grid* mGrid;
//
//  // Move this section somewhere else
//  // This rectangular plane is where cells will reside and drawn
////  Rectangle plane;
//
//// Create animation in a different way
////  class TextAnimation
////  {
////  public:
////    TextAnimation() = default;
////    TextAnimation(float targetRotation, bool isClockwise, float speed);
////    bool Animate(float* currentRotation);
////    void Reset();
////
////  private:
////    bool isFinished;
////    bool isStarted;
////    bool isClockwise;
////    float targetRotation;
////    float speed;
////  };
//
////  TextAnimation textAnimation, textAnimation1, textAnimation2;
//
//  // Logo
////  Font font;
////  float rotation = 0;
////  float speed = 50;
////  Vector2 initial, final;
////  void DrawLogo();
//
//
////  Vector2 pixelLength;
//
//// Move to a grid specific class
////  std::vector<std::vector<Cell*>> grid;
////  std::vector<Cell*> mineCells;
////  int rows;
////  int columns;
////  int totalMines;
////  int totalSeals;
////  void SetMineCells();
////
////  void SetAdjacentCellsAround(Cell* cell);
////
////  void GetAdjacentCellsFor(Cell* cell, std::vector<Cell*>& adjacentCells);
////
////  void Expose(Cell* cell);
////
////  void ShowAllMines();
//};
