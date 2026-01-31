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

    windowWidth = 800;
    windowHeight = 600;

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

    int logicalWidth = 640;
    int logicalHeight = 320;
    SDL_SetRenderLogicalPresentation(mRenderer, logicalWidth, logicalHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    loadData();

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
}

void Game::update()
{
}

void Game::render()
{
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);

    SDL_FRect src {
        .x = 0.0f,
        .y = 0.0f,
        .w = 192.0f,
        .h = 192.0f
    };

    SDL_FRect dst {
        .x = 0.0f,
        .y = 0.0f,
        .w = 64.0f,
        .h = 64.0f
    };

    SDL_RenderTexture(mRenderer, playerIdle, &src, &dst);

    SDL_RenderPresent(mRenderer);
}

void Game::loadData()
{
    playerIdle = IMG_LoadTexture(mRenderer, "assets/player/player_sheet.png");
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