#pragma once 

#include "Component/Component.h"
#include "SDL3/SDL.h"

class SpriteComponent : public Component
{
public:
	
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void draw(SDL_Renderer* renderer);
	virtual void setTexture(SDL_Texture* texture);

	int getDrawOrder() const { return mDrawOrder; }
	int getTexHeight() const { return mTexHeight; }
	int getTexWidth() const { return mTexWidth; }
	void setTexWidth(int width) { mTexWidth = width;  }
	void setTexHeight(int height) { mTexHeight = height; }
    
protected:
	SDL_Texture* mTexture;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
};