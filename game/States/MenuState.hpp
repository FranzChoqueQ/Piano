#pragma once
#include "GameState.hpp"
#include "engine/graphics/shapes/BotonRectangular.hpp"

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
private:
    std::unique_ptr<BotonRectangular> botonInicio;
};
