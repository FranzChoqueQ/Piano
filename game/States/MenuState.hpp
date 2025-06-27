#pragma once
#include "GameState.hpp"

class MenuState : public GameState {
public:
    MenuState(StateManager& manager);
    //MenuState();
    void enter() override;
    void exit() override;
    void update(float deltaTime) override;
    void render(Window& window) override;
    void handleEvents(EventHandler& eventHandler) override;

    StateManager& stateManager;
};
