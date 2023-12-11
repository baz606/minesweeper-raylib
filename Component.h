//
// Created by shehbaz on 12/10/2023.
//

#pragma once

class Component
{
public:
  // Constructor - lower the update order, the earlier the component updates
  Component(class Actor* owner, int updateOrder = 100);
  // Destructor
  virtual ~Component();
  // Update component using delta time
  virtual void Update(float deltaTime);

  int GetUpdateOrder() const { return mUpdateOrder; }

protected:
  // The actor that owns this component
  class Actor* mOwner;
  // Update order of this component
  int mUpdateOrder;
};
