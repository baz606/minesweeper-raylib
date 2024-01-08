//
// Created by shehbaz on 12/12/2023.
//

#pragma once

#include "DrawComponent.h"
#include "Actor.h"

class TextComponent : public DrawComponent
{
public:
  TextComponent(const std::string& name, Actor* owner, int drawOrder = 100);

  void Draw() override;

  // Setters/Getters
  void SetText(const std::string& text);
  [[nodiscard]] const std::string& GetText() const { return mText; }
  void SetFont(const Font& font) { mFont = font; }
  [[nodiscard]] const Font& GetFont() const { return mFont; }
  void SetColor(const Color& color) { mColor = color; }
  [[nodiscard]] const Color& GetColor() const { return mColor; }
  void SetSpacing(float spacing) { mSpacing = spacing; }
  [[nodiscard]] float GetSpacing() const { return mSpacing; }
  void SetFontSize(float fontSize) { mFontSize = fontSize; }
  [[nodiscard]] float GetFontSize() const { return mFontSize; }

private:
  std::string mText;
  Font mFont;
  Color mColor;
  float mSpacing;
  float mFontSize;
};
