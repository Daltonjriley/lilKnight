#pragma once

#include <Entity/Actor/Actor.h>

class Player : public Actor
{
public:
    Player(class Game* game);
    void updateActor(float deltaTime) override;
	void processKeyboard(const bool* state);
	float getSpeed() const { return mSpeed; }

private:
    float mSpeed;
};