//
// Created by shehbaz on 12/6/2023.
//

#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include "raylib.h"

class Game
{
public:
  enum GameState
  {
    SPLASH_SCREEN,
    MENU,
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

  // Setters/Getters
  void SetGameState(GameState gameState) { mGameState = gameState; }
  [[nodiscard]] GameState GetGameState() const { return mGameState; }
  [[nodiscard]] const Font& GetFont() const { return mFont; }
  int GetScreenWidth() const { return mScreenWidth; }
  int GetScreenHeight() const { return mScreenHeight; }
  std::unordered_map<std::string, Sound>& GetSoundMap() { return mSoundMap; }

  void PlaySoundFromMap(const std::string& name, float volume = 1.0f);

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

  // Current game state and end conditions
  GameState mGameState;
  bool mIsRunning;

  // Actor HashMap -> Update actors based on game state
  std::unordered_map<GameState, std::vector<class Actor*>*> mActorsMap;
  // DrawComponent HashMap -> Render actor draw components based on game state
  std::unordered_map<GameState, std::vector<class DrawComponent*>*> mDrawsMap;
  // HashMap to store all sounds in the game
  std::unordered_map<std::string, Sound> mSoundMap;

  // Game Specific
  // This mGrid contains all cells
  class Grid* mGrid;
  // Logo actor on the Splash Screen
  class Logo* mLogo;
  // Caption under the logo
  class Actor* mCaption;
  Font mFont;
};
