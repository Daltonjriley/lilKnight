#pragma once

#include <cstdint>

class Component 
{
public:
    Component(class Actor* owner, int updateOrder = 100);
    virtual ~Component();

    virtual void update(float deltaTime);
    virtual void processInput(const bool* keyState) {}

    class Actor* getOwner() { return mOwner; }
    int getUpdateOrder() const { return mUpdateOrder; }

protected:
    class Actor* mOwner;
    int mUpdateOrder;
};