#include "game/Game.h"

int main(int argc, char* argv[]) {
    Game game;
    bool initialized = game.initialize();

    if (initialized) {
        game.runLoop();
    }
    game.shutdown();
    return 0;
}