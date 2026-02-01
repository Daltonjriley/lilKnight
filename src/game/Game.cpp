#include "Game.h"

#include <iostream>

Game::Game()
    : mWindow(nullptr)
    , mRenderer(nullptr)
    , mRunning(true)
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
    if (keyboard[SDL_SCANCODE_A])
    {
        movedir = -1.0f;
        flipPlayer = true;
    }
    if (keyboard[SDL_SCANCODE_D])
    {
        movedir = 1.0f;
        flipPlayer = false;
    }
    if (!keyboard[SDL_SCANCODE_A] && !keyboard[SDL_SCANCODE_D])
    {
        movedir = 0.0f;
    }
    if (keyboard[SDL_SCANCODE_A] && keyboard[SDL_SCANCODE_D])
    {
        movedir = 0.0f;
    }
    
    

}

void Game::update()
{
    #define SDL_TICKS_PASSED(A, B)  ((Sint32)((B) - (A)) <= 0)
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

    playerX += movedir * 100.0f * deltaTime;
}

void Game::render()
{
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);

    SDL_FRect src {
        .x = 0.0f,
        .y = 0.0f,
        .w = SPRITE_SIZE_ACTUAL_W,
        .h = SPRITE_SIZE_ACTUAL_H
    };

    SDL_FRect dst {
        .x = playerX,
        .y = FLOOR - SPRITE_SIZE,
        .w = SPRITE_SIZE,
        .h = SPRITE_SIZE
    };

    SDL_RenderTextureRotated(mRenderer, playerIdle, &src, &dst, 0.0f, nullptr, 
        flipPlayer ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);

    SDL_RenderPresent(mRenderer);
}

void Game::loadData()
{
    playerIdle = IMG_LoadTexture(mRenderer, "assets/player/IDLE.png");
    SDL_SetTextureScaleMode(playerIdle, SDL_SCALEMODE_NEAREST);
}

void Game::unloadData()
{
    SDL_DestroyTexture(playerIdle);
}

void Game::shutdown()
{
    unloadData();
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}