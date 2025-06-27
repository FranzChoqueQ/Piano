#include "MenuState.hpp"
#include "PlayState.hpp"
#include "StateManager.hpp"
#include "PauseState.hpp"  // Necesario para crear el estado de pausa
#include <SDL2/SDL_ttf.h>
#include <stdexcept>
//#include "PlayState.hpp"

MenuState::MenuState(StateManager& manager) : stateManager(manager) {}

void MenuState::enter() {
    // Inicialización específica del menú
    if (!textRender.loadFont("assets/fonts/arial.ttf", 36)) {
        throw std::runtime_error("No se pudo cargar la fuente en PlayState");
    }
}

void MenuState::exit() {
    // Limpieza
}

void MenuState::update(float deltaTime) {
    // Lógica de actualización del menú
}

void MenuState::render(Window& window) {
    window.clear();
    //textRender.loadFont("assets/fonts/arial.ttf", 36);
    // Renderizar texto "Aquí es el menú"
    const std::string menuText = "Presiona K para iniciar";
    SDL_Color white = {255, 100, 255, 255};
    //int textX = (screenWidth - textRenderer.getTextWidth(menuText)) / 2;
    //int textY = (screenHeight / 2) - 50;
    textRender.render(window.getRenderer(), menuText, 100, 280, white);
    
    window.present();
}

void MenuState::handleEvents(EventHandler& eventHandler) {
    eventHandler.pollEvents();

    if (eventHandler.isKeyPressed(SDL_SCANCODE_K)) {
        stateManager.submitRequest(RequestChangeState{
            std::make_unique<PlayState>(stateManager)
        });
    }
}