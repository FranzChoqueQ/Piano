#include "game/MainGame.hpp"
#include <iostream>

int WinMain(int argc, char* argv[]) {
    try {
        MainGame game;
        game.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}