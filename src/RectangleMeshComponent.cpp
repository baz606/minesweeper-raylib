//
// Created by shehbaz on 12/10/2023.
//

#include "RectangleMeshComponent.h"
#include "Cell.h"

RectangleMeshComponent::RectangleMeshComponent(const std::string& name, Actor *owner, int drawOrder)
: DrawComponent(name, owner, drawOrder)
{
  mThickness = 0.0f;
}

void RectangleMeshComponent::Draw()
{
//  mPosX = mOwner->GetPosition().x - ((float)mWidth / 2);
//  mPosY = mOwner->GetPosition().y - ((float)mHeight / 2);

  mRectangle = { (float)mPosX - ((float)mWidth / 2),
                 (float)mPosY - ((float)mHeight / 2),
                 (float)mWidth * mOwner->GetScale(),
                 (float)mHeight * mOwner->GetScale()};

  DrawRectangleRec(mRectangle, mColor);
  DrawRectangleLinesEx(mRectangle, mThickness, mBorderColor);

  // TODO: Move this line drawing code to another component
  auto cell = (Cell*)mOwner;
  if (cell)
  {
    if (cell->GetCellType() == SEALED
        || cell->GetCellType() == MINE_SEALED)
    {
      // Draw the cross line
      float x1, y1, x2, y2;
      x1 = mPosX - (Cell::LENGTH / 2);
      y1 = mPosY - (Cell::LENGTH / 2);
      x2 = mPosX + (Cell::LENGTH / 2);
      y2 = mPosY + (Cell::LENGTH / 2);
      DrawLineEx({ x1, y1 }, { x2, y2 }, 3.f, BLACK);

      x1 = mPosX + (Cell::LENGTH / 2);
      y1 = mPosY - (Cell::LENGTH / 2);
      x2 = mPosX - (Cell::LENGTH / 2);
      y2 = mPosY + (Cell::LENGTH / 2);
      DrawLineEx({ x1, y1 }, { x2, y2 }, 3.f, BLACK);
    }
  }
}
