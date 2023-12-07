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
  game.CloseGame();
  // Clean up - close window and OpenGL context
  return 0;
}
