#pragma once
#include "engine/core/Game.hpp"
#include "engine/graphics/TextRenderer.hpp"
#include "States/MenuState.hpp"
#include "States/StateManager.hpp"
#include "engine/core/EventHandler.hpp"

class MainGame : public Game {
public:
    MainGame();
    
protected:
    void initialize() override;
    void update(float deltaTime) override;
    void render() override;
    void handleEvents() override;
    
private:
    TextRenderer textRender;
    StateManager stateManager;
    EventHandler eventHandler;

};