#pragma once

#include "utility/animation.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include <string>

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

    uint32_t mTicksCount;

    int windowWidth {1600};
    int windowHeight {900};
    int logicalWidth {640};
    int logicalHeight {320};
    const float FLOOR {static_cast<float>(logicalHeight)};
    bool mRunning;

    float playerX {0.0f};
    float playerY {0.0f};
    float movedir {0.0f};
    bool flipPlayer {false};
    const float SPRITE_SIZE {64.0f};
    const float SPRITE_SIZE_ACTUAL_W {96.0f};
    const float SPRITE_SIZE_ACTUAL_H {84.0f};

};