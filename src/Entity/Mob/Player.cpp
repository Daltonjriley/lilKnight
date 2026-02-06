#include "Player.h"
#include "Game/Game.h"
#include "Component/SpriteComponent.h"

Player::Player(Game* game)
    : Actor(game)
    , mSpeed(0.0f)
{
    SpriteComponent* sc = new SpriteComponent(this, 150);
    sc->setTexture(game->getTexture("assets/player/IDLE.png"));
    sc->setTexWidth(64);
    sc->setTexHeight(64);
}

void Player::updateActor(float deltaTime)
{
    Actor::updateActor(deltaTime);
    glm::vec2 pos = getPosition();
    pos.x += mSpeed * deltaTime;
    setPosition(pos);
}

void Player::processKeyboard(const bool* state)
{
    const float maxSpeed = 250.0f;
    mSpeed = 0.0f;
    if (state[SDL_SCANCODE_A])
    {
        mSpeed -= maxSpeed;
        setFlip(true);
    }
    if (state[SDL_SCANCODE_D])
    {
        mSpeed += maxSpeed;
        setFlip(false);
    }
}