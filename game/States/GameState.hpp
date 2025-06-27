#pragma once

//#include "StateManager.hpp"
#include "engine/core/EventHandler.hpp"
#include "engine/core/Window.hpp"
#include "engine/graphics/TextRenderer.hpp"

// Declaraciones adelantadas
class EventHandler;
class Window;
class StateManager;

class GameState {
public:
    virtual ~GameState() = default;

    virtual void enter() = 0;
    virtual void exit() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render(Window& window) = 0;
    virtual void handleEvents(EventHandler& eventHandler) = 0;

    bool isTransparent() const { return false; } // Para renderizado múltiple
    bool isTranscendent() const { return false; } // Para updates múltiples

    TextRenderer textRender;
    //StateManager stateManager;
};
