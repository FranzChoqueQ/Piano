#pragma once
#include "GameState.hpp"

class StateManager;

class PlayState : public GameState {
public:
    explicit PlayState(StateManager& manager);
    
    void enter() override;
    void exit() override;
    void update(float deltaTime) override;
    void render(Window& window) override;
    void handleEvents(EventHandler& eventHandler) override;
    
private:
    StateManager& stateManager;
    // ... otros miembros ...
};