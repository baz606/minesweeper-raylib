#include "Game.h"

int main()
{
  Game game(1280, 960, "Minesweeper");
  game.Initialize();

  while (!game.ExitGame())
  {
    // Run main game loop
    game.RunGame();
  }
  // Clean up - close window and deallocate memory
  game.CloseGame();

  return 0;
}
