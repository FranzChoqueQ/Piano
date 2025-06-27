#include "EventHandler.hpp"
#include <SDL2/SDL.h>

EventHandler::EventHandler() {
    currentKeyStates = SDL_GetKeyboardState(&numKeys);      // Estado actual de teclado
    previousKeyStates = new Uint8[numKeys];             // Estado previo del teclado
    std::copy(currentKeyStates, currentKeyStates + numKeys, previousKeyStates);
    
    currentMouseState = SDL_GetMouseState(&mouseX, &mouseY);
    previousMouseState = currentMouseState;
    
    quit = false;
}

void EventHandler::pollEvents() {
    updatePreviousStates();
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                currentKeyStates = SDL_GetKeyboardState(nullptr);
                break;
            case SDL_MOUSEMOTION:
                mouseX = event.motion.x;
                mouseY = event.motion.y;
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                currentMouseState = SDL_GetMouseState(&mouseX, &mouseY);
                break;
        }
    }
}

bool EventHandler::isKeyDown(SDL_Scancode key) const {
    return currentKeyStates[key];
}

bool EventHandler::isKeyPressed(SDL_Scancode key) const {
    return currentKeyStates[key] && !previousKeyStates[key];
}

bool EventHandler::isKeyReleased(SDL_Scancode key) const {
    return !currentKeyStates[key] && previousKeyStates[key];
}

bool EventHandler::isMouseButtonDown(Uint8 button) const {
    return currentMouseState & SDL_BUTTON(button);
}

bool EventHandler::isMouseButtonPressed(Uint8 button) const {
    return (currentMouseState & SDL_BUTTON(button)) && 
           !(previousMouseState & SDL_BUTTON(button));
}

bool EventHandler::isMouseButtonReleased(Uint8 button) const {
    return !(currentMouseState & SDL_BUTTON(button)) && 
           (previousMouseState & SDL_BUTTON(button));
}

void EventHandler::getMousePosition(int& x, int& y) const {
    x = mouseX;
    y = mouseY;
}

bool EventHandler::quitRequested() const {
    return quit;
}

void EventHandler::updatePreviousStates() {
    std::copy(currentKeyStates, currentKeyStates + numKeys, previousKeyStates);
    previousMouseState = currentMouseState;
}