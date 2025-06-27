#include "PlayState.hpp"
#include "StateManager.hpp"
#include "PauseState.hpp"  // Necesario para crear el estado de pausa
#include "MenuState.hpp"   // Necesario para crear el estado de menú
#include <SDL2/SDL_ttf.h>
#include <stdexcept>
#include <iostream>

// Constructor
PlayState::PlayState(StateManager& manager)
    : stateManager(manager), piano(50, 200) {
    //: stateManager(manager), tecladoPiano(0,200) {
    // Inicialización de recursos específicos del estado    
}

void PlayState::enter() {
    // Cargar recursos al entrar al estado
    if (!textRender.loadFont("assets/fonts/arial.ttf", 36)) {
        throw std::runtime_error("No se pudo cargar la fuente en PlayState");
    }
}

void PlayState::exit() {
    // Liberar recursos específicos del estado
}

void PlayState::update(float deltaTime) {
    // Lógica de actualización del juego
}

void PlayState::render(Window& window) {
    window.clear();
    
    //tecladoPiano.render(window.getRenderer());
    //TecladoPiano piano(50, 100);
    piano.render(window.getRenderer());

    /*// Renderizar elementos del juego
    const std::string gameText = "Este es el juego";
    SDL_Color color = {255, 255, 255, 255}; // Blanco
    
    // Obtener dimensiones de la ventana para centrar texto
    int screenWidth, screenHeight;
    SDL_GetWindowSize(window.getSDLWindow(), &screenWidth, &screenHeight);
    
    int textWidth = textRender.getTextWidth(gameText);
    int textX = (screenWidth - textWidth) / 2;
    int textY = (screenHeight / 2) - 50;
    
    textRender.render(window.getRenderer(), gameText, textX, textY, color);
    
    // Renderizar instrucciones
    const std::string instruction1 = "Presiona P para pausar";
    const std::string instruction2 = "Presiona F para volver al menu";
    
    textX = (screenWidth - textRender.getTextWidth(instruction1)) / 2;
    textY += 70;
    textRender.render(window.getRenderer(), instruction1, textX, textY, color);
    
    textX = (screenWidth - textRender.getTextWidth(instruction2)) / 2;
    textY += 40;
    textRender.render(window.getRenderer(), instruction2, textX, textY, color);
*/

    //std::cout << "Cantidad de teclas blancas: " << tecladoPiano.getWhiteKeyCount() << std::endl;
    //Rectangle prueba(100, 100, 200, 50, {255, 0, 0, 255});
    //prueba.render(window.getRenderer());


    window.present();
}

void PlayState::handleEvents(EventHandler& eventHandler) {
    eventHandler.pollEvents();
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