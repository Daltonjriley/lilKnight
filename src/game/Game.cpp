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

    int windowWidth = 800;
    int windowHeight = 600;

    mWindow = SDL_CreateWindow("Lil Knight", windowWidth, windowHeight, 0);
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
            mRunning = false;
            break;
        }    
    }
}

void Game::update()
{
}

void Game::render()
{
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);

    

    SDL_RenderPresent(mRenderer);
}

void Game::shutdown()
{
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}