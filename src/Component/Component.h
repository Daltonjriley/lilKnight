#pragma once

#include <cstdint>

class Component 
{
public:
    Component(class Actor* owner, int updateOrder = 100);
    virtual ~Component();

    virtual void update(float deltaTime);
    virtual void processInput(const uint8_t* keyState) {}

    class Actor* getOwner() { return mOwner; }
    int getUpdateOrder() const { return mUpdateOrder; }
private:
    class Actor* mOwner;
    int mUpdateOrder;
};