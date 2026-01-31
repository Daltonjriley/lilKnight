#pragma once

#include <SDL3/SDL.h>

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
    
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;

    bool mRunning;
};