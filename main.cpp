#include "Game.h"

int main()
{
  Game game(1280, 960, "Minesweeper");
  game.Initialize();

  while (game.IsRunning())
  {
    // Run main game loop
    game.RunGame();
  }
  // Clean up - close window and deallocate memory
  game.Shutdown();

  return 0;
}
