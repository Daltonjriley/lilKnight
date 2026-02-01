#include "Actor.h"
#include "Game/Game.h"
#include "Component/Component.h"
#include <algorithm>

Actor::Actor(Game* game)
    : mState(State::Active)
    , mGame(game)
    , mPosition(0.0f, 0.0f)
    , mScale(1.0f)
    , mRotation(0.0f)
{
    mGame->addActor(this);
}

Actor::~Actor()
{
    mGame->removeActor(this);
    while (!mComponents.empty())
    {
        delete mComponents.back();
    }
}

void Actor::update(float deltaTime)
{
    if (mState == State::Active)
    {
        updateComponents(deltaTime);
        updateActor(deltaTime);
    }
} 

void Actor::updateComponents(float deltaTime)
{
    for (auto comp : mComponents)
    {
        comp->update(deltaTime);
    }
}

void Actor::updateActor(float deltaTime)
{
}

void Actor::processInput(const uint8_t* keyState)
{
    if (mState == State::Active)
    {
        for (auto comp : mComponents)
        {
            comp->processInput(keyState);
        }

        actorInput(keyState);
    }
}

void Actor::actorInput(const uint8_t* keyState)
{
}

void Actor::addComponent(Component* component)
{
    int myOrder = component->getUpdateOrder();
	auto iter = mComponents.begin();
	for (;
		iter != mComponents.end();
		++iter)
	{
		if (myOrder < (*iter)->getUpdateOrder())
		{
			break;
		}
	}

	mComponents.insert(iter, component);
}

void Actor::removeComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}
