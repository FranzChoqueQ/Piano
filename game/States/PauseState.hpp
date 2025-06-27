#pragma once
#include "GameState.hpp"

class PauseState : public GameState {
public:
    explicit PauseState(StateManager& manager); 
    //MenuState();
    void enter() override;
    void exit() override;
    void update(float deltaTime) override;
    void render(Window& window) override;
    void handleEvents(EventHandler& eventHandler) override;

    StateManager& stateManager;  // Referencia al StateManager
};