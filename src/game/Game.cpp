#include "Game.h"
#include "Entity/Actor/Actor.h"
#include "Component/SpriteComponent.h"
#include "Entity/Mob/Player.h"

#include <iostream>
#include <algorithm>

Game::Game()
    : mWindow(nullptr)
    , mRenderer(nullptr)
    , mRunning(true)
    , mUpdatingActors(false)
{
}

bool Game::initialize() {
    int result = SDL_Init(SDL_INIT_VIDEO);
    if (result = 0)
    {
        SDL_Log("Could not initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow("Lil Knight", windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);
    if (!mWindow) 
    {
        SDL_Log("Could not create window: %s", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, nullptr);
    if (!mRenderer) 
    {
        SDL_Log("Could not create renderer: %s", SDL_GetError());
        return false;
    }

    SDL_SetRenderLogicalPresentation(mRenderer, logicalWidth, logicalHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    loadData();

    mTicksCount = SDL_GetTicks();

    return true;
}

void Game::runLoop()
{
   while (mRunning)
   {
         processInput();
         update();
         render();
   }
}

void Game::processInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_EVENT_QUIT:
            {
                mRunning = false;
                break;
            }
            case SDL_EVENT_WINDOW_RESIZED:
            {
                windowWidth = event.window.data1;
                windowHeight = event.window.data2;
                break;
            }
        }    
    }

    const bool *keyboard = SDL_GetKeyboardState(nullptr);
    if (keyboard[SDL_SCANCODE_ESCAPE])
	{
		mRunning = false;
	}

    mPlayer->processKeyboard(keyboard);
}

void Game::update()
{
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();


    mUpdatingActors = true;
    for (auto actor : mActors)
    {
        actor->update(deltaTime);
    }
    mUpdatingActors = false;


    for (auto pending : mPendingActors)
    {
        mActors.emplace_back(pending);
    }
    mPendingActors.clear();


    std::vector<Actor*> deadActors;
    for (auto actor : mActors)
    {
        if (actor->getState() == Actor::State::Dead)
        {
            deadActors.emplace_back(actor);
        }
    }
    for (auto actor : deadActors)
    {
        delete actor;
    }
}

void Game::render()
{
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);

    for (auto sprite : mSprites)
    {
        sprite->draw(mRenderer);
    }

    SDL_RenderPresent(mRenderer);
}

SDL_Texture* Game::getTexture(const std::string& fileName)
{
	SDL_Texture* texture = nullptr;
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		texture = iter->second;
	}
	else
	{
		SDL_Surface* surface = IMG_Load(fileName.c_str());
		if (!surface)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}

		
		texture = SDL_CreateTextureFromSurface(mRenderer, surface);
		SDL_DestroySurface(surface);
		if (!texture)
		{
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}

		mTextures.emplace(fileName.c_str(), texture);
	}
	return texture;
}

void Game::loadData()
{
    mPlayer = new Player(this);
    mPlayer->setPosition(glm::vec2{logicalWidth / 2.0f, FLOOR - SPRITE_SIZE / 2.0f});
    mPlayer->setScale(1.0f);
}

void Game::unloadData()
{
    while (!mActors.empty())
    {
        delete mActors.back();
    }

    for (auto& texture : mTextures)
    {
        SDL_DestroyTexture(texture.second);
    }
    mTextures.clear();
}

void Game::shutdown()
{
    unloadData();
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::addActor(Actor* actor)
{
    if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::removeActor(Actor* actor)
{
    auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::addSprite(SpriteComponent* sprite)
{
	int myDrawOrder = sprite->getDrawOrder();
	auto iter = mSprites.begin();
	for ( ;
		iter != mSprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->getDrawOrder())
		{
			break;
		}
	}
	mSprites.insert(iter, sprite);
}

void Game::removeSprite(SpriteComponent* sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}