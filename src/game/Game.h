#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include <string>
#include <unordered_map>

#define SDL_TICKS_PASSED(A, B)  ((Sint32)((B) - (A)) <= 0)

class Game 
{
public:
    Game();
    bool initialize();
    void runLoop();
    void shutdown();

    void addActor(class Actor* actor);
    void removeActor(class Actor* actor);

    void addSprite(class SpriteComponent* sprite);
	void removeSprite(class SpriteComponent* sprite);
	
	SDL_Texture* getTexture(const std::string& fileName);
    
    
private:
    void processInput();
    void update();
    void render();
    void loadData();
    void unloadData();
    
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;

    uint32_t mTicksCount;
    bool mUpdatingActors;
    bool mRunning;
    std::vector<class Actor*> mActors;
    std::vector<class Actor*> mPendingActors;
    std::vector<class SpriteComponent*> mSprites;
    std::unordered_map<std::string, SDL_Texture*> mTextures;

    class Player* mPlayer;

    int windowWidth {1600};
    int windowHeight {900};
    int logicalWidth {640};
    int logicalHeight {320};

    // to be removed after refactoring
    const float FLOOR {static_cast<float>(logicalHeight)};
    float playerX {0.0f};
    float playerY {0.0f};
    float movedir {0.0f};
    bool flipPlayer {false};
    const float SPRITE_SIZE {64.0f};
    const float SPRITE_SIZE_ACTUAL_W {96.0f};
    const float SPRITE_SIZE_ACTUAL_H {84.0f};
    SDL_Texture* playerIdle;

};