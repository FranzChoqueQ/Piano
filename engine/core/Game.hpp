#pragma once
#include "Window.hpp"
#include "EventHandler.hpp"

class Game {
public:
    Game(const std::string& title, int width, int height);
    virtual ~Game() = default;
    
    void run();
    
protected:
    virtual void initialize() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
    virtual void handleEvents() = 0;
    
    Window window;
    EventHandler eventHandler;
    bool isRunning;
};