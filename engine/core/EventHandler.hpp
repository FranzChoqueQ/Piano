#pragma once
#include <SDL2/SDL.h>
#include <unordered_map>

class EventHandler {
public:
    EventHandler();
    ~EventHandler() = default;

    // Procesa todos los eventos pendientes
    void pollEvents();
    
    // Estado del teclado
    bool isKeyDown(SDL_Scancode key) const;
    bool isKeyPressed(SDL_Scancode key) const;
    bool isKeyReleased(SDL_Scancode key) const;
    
    // Estado del mouse
    bool isMouseButtonDown(Uint8 button) const;
    bool isMouseButtonPressed(Uint8 button) const;
    bool isMouseButtonReleased(Uint8 button) const;
    void getMousePosition(int& x, int& y) const;
    
    // Eventos de ventana
    bool quitRequested() const;

private:
    // Estado actual del teclado
    const Uint8* currentKeyStates;
    
    // Estados del mouse
    Uint32 currentMouseState;
    Uint32 previousMouseState;
    int mouseX, mouseY;
    
    // Estados previos para detección de pulsaciones
    Uint8* previousKeyStates;
    int numKeys;
    
    // Evento de salida
    bool quit;
    
    // Actualiza los estados previos
    void updatePreviousStates();
};