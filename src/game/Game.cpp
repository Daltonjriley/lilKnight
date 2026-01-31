#include "Game.h"
#include <iostream>

Game::Game()
    : mWindow(nullptr)
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

void Game::shutdown()
{
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
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
}