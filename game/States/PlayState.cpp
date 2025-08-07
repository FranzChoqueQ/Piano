#include "PlayState.hpp"
#include "StateManager.hpp"
#include "PauseState.hpp"  
#include "MenuState.hpp"   
#include <SDL2/SDL_ttf.h>
#include <stdexcept>
#include <iostream>

// Constructor
PlayState::PlayState(StateManager& manager)
    : stateManager(manager), piano(50, 200) { 
}

void PlayState::enter() {
    // Cargar recursos al entrar al estado
    if (!textRender.loadFont("assets/fonts/arial.ttf", 36)) {
        throw std::runtime_error("No se pudo cargar la fuente en PlayState");
    }
}

void PlayState::exit() {
    // Liberar recursos
}

void PlayState::update(float deltaTime) {
    piano.update();
}

void PlayState::render(Window& window) {
    window.clear();
    
    piano.render(window.getRenderer());

    window.present();
}

void PlayState::handleEvents(EventHandler& eventHandler) {
    piano.handleEvents(eventHandler);

    if (eventHandler.isKeyPressed(SDL_SCANCODE_LEFTBRACKET)) {
        stateManager.submitRequest(StateRequest{
            RequestPushState{std::make_unique<PauseState>(stateManager)}  // Constructor correcto
        });
    }
    
    if (eventHandler.isKeyPressed(SDL_SCANCODE_SEMICOLON)) {
        stateManager.submitRequest(StateRequest{
            RequestChangeState{std::make_unique<MenuState>(stateManager)}  // Constructor correcto
        });
    }
}