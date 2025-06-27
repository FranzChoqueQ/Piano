#include "MainGame.hpp"
#include <SDL2/SDL_ttf.h>
#include <stdexcept>

MainGame::MainGame() 
    : Game("Mi Primer Juego SDL2", 800, 600){
    }

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
    /*window.clear();
    
    textRender.loadFont("C:/windows/fonts/Georgia.ttf", 36);
    // Renderizar mensaje
    SDL_Color color = {255, 200, 20};
    textRender.render(window.getRenderer(), "Programa que se cierra con la", 100, 280, color);
    textRender.render(window.getRenderer(), "tecla ESCAPE y dando click a la X", 100, 380, color);
    
    window.present();*/
}

void MainGame::handleEvents() {
    //eventHandler.pollEvents();
    stateManager.handleEvents(eventHandler);
    
    if (eventHandler.isKeyDown(SDL_SCANCODE_ESCAPE)) {
        isRunning = false;
    }

    if(eventHandler.quitRequested()){
        isRunning = false;
    }
}

/*
void MainGame::renderText(const std::string& message, int x, int y) {
    TTF_Font* font = TTF_OpenFont("assets/fonts/arial.ttf", 25);        //assets/fonts/arial.ttf
    if (!font) {
        throw std::runtime_error("Failed to load font: " + std::string(TTF_GetError()));
    }
    
    SDL_Color color = {255, 255, 255, 255}; // Blanco
    SDL_Surface* surface = TTF_RenderText_Solid(font, message.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(window.getRenderer(), surface);
    
    SDL_Rect rect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(window.getRenderer(), texture, nullptr, &rect);
    
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}
*/