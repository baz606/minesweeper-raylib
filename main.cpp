#include "raylib.h"

int main()
{
  // Initializing window
  // Preserve 4:3 aspect ratio to give an arcade game vibe
  const int SCREEN_WIDTH = 1280;
  const int SCREEN_HEIGHT = 960;

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "minesweeper-raylib");
  SetTargetFPS(60);

  while (!WindowShouldClose())
  {
    // Draw
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Test Window", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 50, BLACK);
    EndDrawing();
  }

  // Clean up - close window and OpenGL context
  CloseWindow();
}
