//
// Created by shehbaz on 12/10/2023.
//

#include <algorithm>
#include "Game.h"
#include "Actor.h"
#include "Component.h"

Actor::Actor(Game *game)
:mState(EActive)
,mPosition({ 0, 0 })
,mScale(1.0f)
,mRotation(0.0f)
,mGame(game)
{
  mGame->AddActor(this);
}

Actor::~Actor()
{
  mGame->RemoveActor(this);
  // Delete components for this actor
  while (!mComponents.empty())
  {
    delete mComponents.back();
  }
}

void Actor::Update(float deltaTime)
{
  if (mState == EActive)
  {
    UpdateComponents(deltaTime);
    UpdateActor(deltaTime);
  }
}

void Actor::UpdateComponents(float deltaTime)
{
  for (auto component : mComponents)
  {
    component->Update(deltaTime);
  }
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::SetPosition(float x, float y)
{
  mPosition.x = x;
  mPosition.y = y;
}

void Actor::AddComponent(Component *component)
{
  // Find the insertion point in the sorted vector
  int myOrder = component->GetUpdateOrder();
  auto iter = mComponents.begin();
  for (; iter != mComponents.begin(); ++iter)
  {
    if (myOrder < (*iter)->GetUpdateOrder())
    {
      break;
    }
  }
  // Insert component before position of the iterator
  mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component *component)
{
  auto iter = std::find(mComponents.begin(), mComponents.end(), component);
  if (iter != mComponents.end())
  {
    mComponents.erase(iter);
  }
}

void Actor::AddComponentToMap(std::string &name, Component* component)
{
  mComponentsMap.insert(std::make_pair(name, component));
}

void Actor::RemoveComponentFromMap(std::string &name)
{
  mComponentsMap.erase(name);
}

Component* Actor::GetComponent(const std::string& name)
{
  return mComponentsMap.find(name)->second;
}
