#include "StateManager.hpp"

void StateManager::pushState(std::unique_ptr<GameState> state) {
    if (!states.empty()) {
        states.top()->exit();
    }
    states.push(std::move(state));
    states.top()->enter();
}

void StateManager::popState() {
    if (!states.empty()) {
        states.top()->exit();
        states.pop();
    }
    if (!states.empty()) {
        states.top()->enter();
    }
}

void StateManager::changeState(std::unique_ptr<GameState> state) {
    while (!states.empty()) {
        popState();
    }
    pushState(std::move(state));
}

void StateManager::update(float deltaTime) {
    if (!states.empty()) {
        states.top()->update(deltaTime);
    }
}

void StateManager::render(Window& window) {
    if (!states.empty()) {
        states.top()->render(window);
    }
}

void StateManager::handleEvents(EventHandler& eventHandler) {
    if (!states.empty()) {
        states.top()->handleEvents(eventHandler);
    }
}

bool StateManager::isEmpty() const {
    return states.empty();
}

void StateManager::submitRequest(StateRequest request) {
    requestHandler.handleRequest(std::move(request));
}

void StateManager::processRequests() {
    requestHandler.applyRequests(*this);
    
    // Opcional: limpieza de estados muertos
    while (!states.empty() && states.top() == nullptr) {
        states.pop();
    }
}