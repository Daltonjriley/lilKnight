#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class Game 
{
public:
    Game();
    bool initialize();
    void runLoop();
    void shutdown();
    
private:

    void processInput();
    void update();
    void render();
    void loadData();
    void unloadData();
    
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;

    SDL_Texture* playerIdle;

    bool mRunning;
};