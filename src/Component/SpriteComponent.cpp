#include "SpriteComponent.h"
#include "Entity/Actor/Actor.h"
#include "Game/Game.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
    : Component(owner)
    , mTexture(nullptr)
    , mDrawOrder(drawOrder)
    , mTexWidth(0)
    , mTexHeight(0)
{
    mOwner->getGame()->addSprite(this);
}

SpriteComponent::~SpriteComponent()
{
    mOwner->getGame()->removeSprite(this);
}

void SpriteComponent::draw(SDL_Renderer* renderer)
{
    if (mTexture)
    {
        SDL_SetTextureScaleMode(mTexture, SDL_SCALEMODE_NEAREST);

        SDL_FRect dst {
        .x = mOwner->getPosition().x - dst.w / 2,
        .y = mOwner->getPosition().y - dst.h / 2,
        .w = (mTexWidth * mOwner->getScale()),
        .h = (mTexHeight * mOwner->getScale())
        };

        SDL_RenderTextureRotated(renderer, mTexture, nullptr, &dst, glm::degrees(mOwner->getRotation()), nullptr, 
                                 (mOwner->getFlip()) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);

    }
}

void SpriteComponent::setTexture(SDL_Texture* texture)
{
    mTexture = texture;
}