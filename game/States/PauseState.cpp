#include "PauseState.hpp"
#include "engine/core/Window.hpp"
#include "engine/core/EventHandler.hpp"
#include "StateManager.hpp"
#include <SDL2/SDL_ttf.h>
#include <string>
#include <stdexcept>

PauseState::PauseState(StateManager& manager) 
    : stateManager(manager) {}

void PauseState::enter() {
    if (!textRender.loadFont("assets/fonts/arial.ttf", 36)) {
        throw std::runtime_error("No se pudo cargar la fuente en PlayState");
    }
}

void PauseState::exit() {
    // Limpieza
}

void PauseState::update(float deltaTime) {
    // Lógica de actualización
}

void PauseState::render(Window& window) {
    window.clear();
    const std::string menuText = "Presiona P para volver";
    SDL_Color white = {255, 100, 255, 255};
    textRender.render(window.getRenderer(), menuText, 100, 280, white);
    // Renderizado del menú de pausa
    window.present();
}

void PauseState::handleEvents(EventHandler& eventHandler) {
    if (eventHandler.isKeyPressed(SDL_SCANCODE_LEFTBRACKET)) {
        stateManager.popState();
    }
}