//
// Created by shehbaz on 12/12/2023.
//

#include "TextComponent.h"

TextComponent::TextComponent(const std::string &name, Actor *owner, int drawOrder)
:DrawComponent(name, owner, drawOrder)
{
}

void TextComponent::Draw()
{
  if (mIsShow)
  {
    DrawTextEx(mFont,
               mText.c_str(),
               { (float)mPosX, (float)mPosY },
               mFontSize,
               mSpacing,
               mColor);
  }
}

void TextComponent::CalculatePosition()
{
  int currentX = (int)mOwner->GetPosition().x;
  int currentY = (int)mOwner->GetPosition().y;

  Vector2 textLength = MeasureTextEx(mFont, mText.c_str(), mFontSize, mSpacing);
  currentX -= (int)textLength.x / 2;
  currentY -= (int)textLength.y / 2;

  mPosX = currentX;
  mPosY = currentY;
}

// This method should be the last setter after all the other attributes are set
void TextComponent::SetText(const std::string &text)
{
  mText = text;
  // Re-calculate the position of this text component to accurately draw
  CalculatePosition();
}
