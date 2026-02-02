#pragma once

#include <vector>
#include <glm/glm.hpp>

class Actor
{
public:
    Actor(class Game* game);
    virtual ~Actor();

    enum class State
    {
        Active,
        Paused,
        Dead
    };

    void update(float deltaTime);
    void updateComponents(float deltaTime);
    virtual void updateActor(float deltaTime);

    void processInput(const bool* keyState);
    virtual void actorInput(const bool* keyState);

    glm::vec2 getForward() const 
    {
        return glm::vec2{cosf(mRotation), sinf(mRotation)};
    }

    void addComponent(class Component* component);
    void removeComponent(class Component* component);

    const glm::vec2& getPosition() const { return mPosition; }
    void setPosition(const glm::vec2& pos) { mPosition = pos; }
    float getScale() const { return mScale; }
    void setScale(float scale) { mScale = scale; }
    float getRotation() const { return mRotation; }
    void setRotation(float rotation) { mRotation = rotation; }
    State getState() const { return mState; }
    void setState(State state) { mState = state; }
    bool getFlip() const { return mFlip; }
    void setFlip(bool flip) { mFlip = flip; }
    class Game* getGame() { return mGame; }
    
private:
    State mState;
    class Game* mGame;
    std::vector<class Component*> mComponents;

    glm::vec2 mPosition;
    float mScale;
    float mRotation;
    bool mFlip;
};