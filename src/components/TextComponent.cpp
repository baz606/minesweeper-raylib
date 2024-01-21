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
    Vector2 textLength = MeasureTextEx(mFont,
                                       mText.c_str(),
                                       mFontSize * mOwner->GetScale(),
                                       mSpacing);
    DrawTextPro(mFont,
                mText.c_str(),
                { mOwner->GetPosition().x, mOwner->GetPosition().y },
                { textLength.x / 2, textLength.y / 2 },
                mOwner->GetRotation(),
                mFontSize * mOwner->GetScale(),
                mSpacing,
                mColor);
  }
}

// This method should be the last setter after all the other attributes are set
void TextComponent::SetText(const std::string &text)
{
  mText = text;
}
