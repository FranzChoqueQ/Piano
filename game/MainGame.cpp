#include "MainGame.hpp"
#include <SDL2/SDL_ttf.h>
#include <stdexcept>

MainGame::MainGame() 
    : Game("Piano SDL2", 900, 650){}

void MainGame::initialize() {
    if (TTF_Init() == -1) {
        throw std::runtime_error("Failed to initialize SDL_ttf: " + std::string(TTF_GetError()));
    }
    stateManager.changeState(std::make_unique<MenuState>(stateManager));
    isRunning = true;
}

void MainGame::update(float deltaTime) {
    stateManager.processRequests();
    stateManager.update(deltaTime);
}

void MainGame::render() {
    stateManager.render(window);
}

void MainGame::handleEvents() {
    eventHandler.pollEvents();
    stateManager.handleEvents(eventHandler);
    if (eventHandler.isKeyDown(SDL_SCANCODE_ESCAPE)) {
        isRunning = false;
    }
    if(eventHandler.quitRequested()){
        isRunning = false;
    }
}

