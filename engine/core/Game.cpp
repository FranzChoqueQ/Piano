#include "Game.hpp"
#include <stdexcept>

Game::Game(const std::string& title, int width, int height) 
    : window(title, width, height), 
      eventHandler(),
      isRunning(false) {
    // Inicialización básica del juego
}

void Game::run() {
    initialize();
    isRunning = true;

    // Variables para el control del tiempo
    Uint32 previousTime = SDL_GetTicks();
    float deltaTime = 0.0f;

    // Bucle principal del juego
    while (isRunning) {
        Uint32 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - previousTime) / 1000.0f; // Convertir a segundos
        previousTime = currentTime;

        handleEvents();
        update(deltaTime);
        render();
    }
}