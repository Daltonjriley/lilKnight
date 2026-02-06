#pragma once
#include "Component/SpriteComponent.h"
#include <vector>

class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
	void update(float deltaTime) override;
	void setAnimTextures(const std::vector<SDL_Texture*>& textures);
	
	float getAnimFPS() const { return mAnimFPS; }
	void setAnimFPS(float fps) { mAnimFPS = fps; }
private:
	
	std::vector<SDL_Texture*> mAnimTextures;
	SDL_Texture* mAnimSheet;
	float mCurrFrame;
	float mAnimFPS;
};