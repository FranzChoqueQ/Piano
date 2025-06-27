#pragma once
#include <memory>
#include <stack>
#include "GameState.hpp"
#include "StateRequest.hpp"

// Declaración adelantada
class Window;
class EventHandler;

class StateManager {
public:
    void pushState(std::unique_ptr<GameState> state);
    void popState();
    void changeState(std::unique_ptr<GameState> state);
    
    void update(float deltaTime);
    void render(Window& window);
    void handleEvents(EventHandler& eventHandler);
    
    bool isEmpty() const;

    void processRequests();
    void submitRequest(StateRequest request);
private:
    std::stack<std::unique_ptr<GameState>> states;
    StateRequestHandler requestHandler;
};