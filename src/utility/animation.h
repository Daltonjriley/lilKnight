#pragma once

#include "timer.h"

class Animation
{
public:
    Animation()
        : timer(0.0f)
        , frameCount(0)
    {
    }

    Animation(int frameCount, float frameLength)
        : timer(frameLength)
        , frameCount(frameCount)
    {
    }

    float getLenghth() const { return timer.getLength(); }

    int currentFrame() const 
    { 
        return static_cast<int>(timer.getTime() / timer.getLength() * frameCount); 
    }

    void step(float deltaTime)
    {
        timer.step(deltaTime);
    }
    
private:
    Timer timer;
    int frameCount;
};
