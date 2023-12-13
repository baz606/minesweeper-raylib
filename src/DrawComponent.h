//
// Created by shehbaz on 12/12/2023.
//

#pragma once

#include "Component.h"

class DrawComponent : public Component
{
public:
  DrawComponent(const std::string& name, class Actor* owner, int drawOrder = 100);
  ~DrawComponent() override;

  virtual void Draw() = 0;

  void SetDrawOrder(int drawOrder) { mDrawOrder = drawOrder; }
  [[nodiscard]] int GetDrawOrder() const { return mDrawOrder; }
  void SetPosition(float posX, float posY);
  void SetIsShow(bool isShow) { mIsShow = isShow; }
  [[nodiscard]] bool GetIsShow() const { return mIsShow; }

protected:
  int mDrawOrder;
  float mPosX, mPosY;
  bool mIsShow;
};
