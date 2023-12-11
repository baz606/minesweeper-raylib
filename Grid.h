//
// Created by shehbaz on 12/10/2023.
//

#pragma once

#include <vector>
#include "Actor.h"

class Grid : public Actor
{
public:
  Grid(class Game* game, int rows, int columns, int mines);
  ~Grid() = default;

  void Initialize();
//  void UpdateActor(float deltaTime) override;
//  void ProcessMouse(float mouseX, float mouseY);

private:
  std::vector<std::vector<class Cell*>> mCellList;
  int mRows;
  int mColumns;
  int mMines;
};
