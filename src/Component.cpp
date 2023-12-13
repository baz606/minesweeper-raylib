//
// Created by shehbaz on 12/10/2023.
//

#include "Component.h"
#include "Actor.h"

Component::Component(Actor *owner, const std::string& name, int updateOrder)
:mOwner(owner)
,mUpdateOrder(updateOrder)
,mName(name)
{
  // Add to actor's vector of components
  mOwner->AddComponent(this);
  mOwner->AddComponentToMap(mName, this);
}

Component::~Component()
{
  mOwner->RemoveComponent(this);
  mOwner->RemoveComponentFromMap(mName);
}

void Component::Update(float deltaTime)
{
}
