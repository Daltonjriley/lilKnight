#include "AnimatedSpriteComponent.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	, mCurrFrame(0.0f)
	, mAnimFPS(24.0f)
{
}

void AnimSpriteComponent::update(float deltaTime)
{
	SpriteComponent::update(deltaTime);

	if (mAnimTextures.size() > 0)
	{
		mCurrFrame += mAnimFPS * deltaTime;
		
		while (mCurrFrame >= mAnimTextures.size())
		{
			mCurrFrame -= mAnimTextures.size();
		}

		setTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
	}
}

void AnimSpriteComponent::setAnimTextures(const std::vector<SDL_Texture*>& textures)
{
	mAnimTextures = textures;
	if (mAnimTextures.size() > 0)
	{
		mCurrFrame = 0.0f;
		setTexture(mAnimTextures[0]);
	}
}
