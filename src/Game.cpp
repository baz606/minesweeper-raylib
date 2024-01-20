//
// Created by shehbaz on 12/6/2023.
//

#include <algorithm>
#include <filesystem>

#include "Game.h"
#include "Grid.h"
#include "Cell.h"
#include "DrawComponent.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "Animator.h"
#include "SpriteComponent.h"
#include "BoxCollider.h"
#include "BackButton.h"
#include "TextComponent.h"
#include "TransformAnimation.h"
#include "FlashingAnimation.h"
#include "Logo.h"

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
  SetTraceLogLevel(LOG_ERROR);
  InitAudioDevice();

  // Initialize the actor and draw map
  mActorsMap[SPLASH_SCREEN] = new std::vector<Actor*>;
  mActorsMap[PLAYING] = new std::vector<Actor*>;
  mDrawsMap[SPLASH_SCREEN] = new std::vector<DrawComponent*>;
  mDrawsMap[PLAYING] = new std::vector<DrawComponent*>;

  // Load font
  mFont = LoadFontEx("./resources/lets-eat.ttf", 200, nullptr, 0);
  // Load textures to be used for back button in PLAYING state
  Texture2D onHover, offHover;
  onHover = LoadTexture("./resources/back-blue.png");
  offHover = LoadTexture("./resources/back.png");

  // Load all the sounds under resources/sounds/ directory
  const std::string directory_path = "./resources/sounds";
  std::string name, path;
  for (const auto& entry : std::filesystem::directory_iterator(directory_path))
  {
    name = entry.path().filename().string();
    path = "./resources/sounds/" + name;
    mSoundMap[name] = LoadSound(path.c_str());
  }

  // Create logo actor to display logo in SPLASH_SCREEN state
  mLogo = new Logo(this, SPLASH_SCREEN);
  mLogo->SetPosition(mScreenWidth / 2.f, -100.f);
  mLogo->Init();

  // Add Caption under the logo in SPLASH_SCREEN state
  // TODO: Add textLength as a member variable to TextComponent so we can draw a text relative to another
  mCaption = new Actor(this, SPLASH_SCREEN);
  mCaption->SetPosition((mScreenWidth / 2.f) + 50.f, (mScreenHeight / 2.f) + 200.f);
  // Add Text component for caption
  auto textComp = new TextComponent("TextComponent", mCaption);
  textComp->SetText("PRESS ANY KEY TO CONTINUE...");
  textComp->SetColor(BLACK);
  textComp->SetFont(mFont);
  textComp->SetFontSize(80);
  textComp->SetSpacing(0);
  textComp->SetIsShow(false);
  // Add Animation
  auto animator = new Animator("Animator", mCaption);
  new FlashingAnimation(animator, textComp, 1.f);

  // Initialize the grid with rows x columns cells
  mGrid = new Grid(this, PLAYING, 9, 9, 9);
  mGrid->Initialize();

  auto backButton = new BackButton(this, PLAYING);
  backButton->SetPosition({ mScreenWidth - 100.f, mScreenHeight - 100.f });
  backButton->SetScale(0.5f);
  backButton->SetOnHoverTexture(onHover);
  backButton->SetOffHoverTexture(offHover);

  // Setup back button's components
  new SpriteComponent("SpriteComponent", backButton);
  auto boxCollider = new BoxCollider("BoxCollider", backButton);
  boxCollider->SetCollider(backButton->GetPosition().x - (offHover.width / 2.f), backButton->GetPosition().y - (offHover.height / 2.f), offHover.width, offHover.height);
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
    Animator* logoAnimator = (Animator*)(mLogo->GetComponent("Animator"));
    if (logoAnimator)
    {
      if (logoAnimator->IsDone())
      {
        Animator* captionAnimation = (Animator*)(mCaption->GetComponent("Animator"));
        if (captionAnimation)
        {
          captionAnimation->Play();
        }
        else
        {
          TraceLog(LOG_ERROR, "No Animator in Caption!!!");
        }
        if (GetKeyPressed() > 0)
        {
          PlaySoundFromMap("to-menu.wav");
          mGameState = MENU;
        }
      }
    }
    else
    {
      TraceLog(LOG_ERROR, "No Animator in Logo!!!");
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
    if (IsKeyReleased(KEY_SPACE) || IsKeyReleased(KEY_R))
    {
      mGrid->Reset();
    }
  }
}

void Game::UpdateGame()
{
  switch (mGameState)
  {
    case SPLASH_SCREEN:
    {
      std::vector<Actor*>* actors = mActorsMap[SPLASH_SCREEN];
      for (auto& actor : *actors)
      {
        actor->Update(GetFrameTime());
      }
    }
    break;
    case MENU:
      // Empty MENU state
    break;
    case PLAYING:
    case GAME_OVER:
    case WIN:
    {
      std::vector<Actor*>* actors = mActorsMap[PLAYING];
      for (auto& actor : *actors)
      {
        actor->Update(GetFrameTime());
      }
    }
    break;
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
      std::vector<DrawComponent*>* draws = mDrawsMap[SPLASH_SCREEN];
      for (auto& drawCom: *draws)
      {
        drawCom->Draw();
      }
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
        TraceLog(LOG_DEBUG, "START GAME!");
        PlaySoundFromMap("mouse-click.wav");
        mGrid->Reset();
        mGameState = PLAYING;
      }
      if (GuiButton({(mScreenWidth / 2.f) - (buttonWidth / 2.f),
                     (mScreenHeight / 2.f) - (buttonHeight / 2.f) + buttonHeight,
                     buttonWidth,
                     buttonHeight},
                    "EXIT"))
      {
        TraceLog(LOG_DEBUG, "EXIT GAME!");
        PlaySoundFromMap("mouse-click.wav");
        // Wait for the full click sound before exiting the game
        while (IsSoundPlaying(mSoundMap["mouse-click.wav"]))
        {
        }
        mIsRunning = false;
      }
    }
    break;
    case PLAYING:
    case GAME_OVER:
    case WIN:
    {
      // This is our default PLAYING rendering output
      // This way we can render our GAME_OVER and WIN rectangular box on top of the grid
      ClearBackground(LIGHTGRAY);
      DrawTextEx(mFont,
                 std::string("MINES: " + std::to_string(mGrid->GetTotalSeals())).c_str(),
                 { (float)mScreenWidth - 300, 100 },
                 90, 0, RED);

      Vector2 pixelLength = MeasureTextEx(mFont, "@baz606", 100, 0);
      Vector2 final = { (float)mScreenWidth - 320 + (pixelLength.x / 2), ((float)mScreenHeight / 2 ) + (pixelLength.y / 2) };
      DrawTextPro(mFont, "@baz606", final, { pixelLength.x / 2, pixelLength.y / 2 }, 0.f, 100, 0, VIOLET);

      std::vector<DrawComponent*>* draws = mDrawsMap[PLAYING];
      for (auto& drawCom: *draws)
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
  mActorsMap[actor->GetGameState()]->emplace_back(actor);
}

void Game::RemoveActor(Actor *actor)
{
  std::vector<Actor*>* actors = mActorsMap[actor->GetGameState()];
  auto iter = std::find(actors->begin(), actors->end(), actor);
  if (iter != actors->end())
  {
    actors->erase(iter);
  }
}

void Game::AddDraw(DrawComponent *mesh)
{
  std::vector<DrawComponent*>* draws = mDrawsMap[mesh->GetOwner()->GetGameState()];
  int myDrawOrder = mesh->GetDrawOrder();
  auto iter = draws->begin();
  for (; iter != draws->end(); ++iter)
  {
    if (myDrawOrder < (*iter)->GetDrawOrder())
    {
      break;
    }
  }
  draws->insert(iter, mesh);
}

void Game::RemoveDraw(DrawComponent *mesh)
{
  std::vector<DrawComponent*>* draws = mDrawsMap[mesh->GetOwner()->GetGameState()];

  auto iter = std::find(draws->begin(), draws->end(), mesh);
  if (iter != draws->end())
  {
    draws->erase(iter);
  }
}

bool Game::IsRunning() const
{
  return (!WindowShouldClose() && mIsRunning);
}

void Game::Shutdown()
{
  UnloadData();
  CloseWindow();
}

void Game::UnloadData()
{
  // Delete the actors in the hash map's vector
  for (auto& pair : mActorsMap)
  {
    while (!pair.second->empty())
    {
      delete pair.second->back();
    }
  }
  // Now delete the pointer to the vector
  delete mActorsMap[SPLASH_SCREEN];
  delete mActorsMap[PLAYING];

  // Delete pointer to vector in mDrawsMap
  // The individual deletion of DrawComponent* is handled in their Actor's destructor
  delete mDrawsMap[SPLASH_SCREEN];
  delete mDrawsMap[PLAYING];

  // Unload all sounds in sound hash map
  for (auto& pair : mSoundMap)
  {
    UnloadSound(pair.second);
  }
  mSoundMap.clear();

  UnloadFont(mFont);
}

void Game::PlaySoundFromMap(const std::string& name, float volume)
{
  auto iter = mSoundMap.find(name);
  if (iter != mSoundMap.end())
  {
    Sound sound = mSoundMap[name];
    SetSoundVolume(sound, volume);
    PlaySound(sound);
  }
  else
  {
    TraceLog(LOG_ERROR, "%s sound not found!!!", name.c_str());
  }
}
