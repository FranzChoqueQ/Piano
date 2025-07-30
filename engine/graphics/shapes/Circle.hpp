#pragma once

#include <SDL2/SDL.h>

#include "engine/core/EventHandler.hpp"

class Circle{
public:
    Circle(int x, int y, int radio, SDL_Color color);
    virtual ~Circle();

    void render(SDL_Renderer* renderer) const;
    void handleEvent(const EventHandler& event);
    void setColor(SDL_Color newColor);
    void setPosition(int new_x, int new_y);
    void drawCircle(SDL_Renderer* renderer, int x, int y) const;

    SDL_Color color;
    int x;
    int y;
    int radio;
private:
};
