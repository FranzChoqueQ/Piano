#pragma once

#include "Rectangle.hpp"
//#include <functional>

class BotonRectangular : public Rectangle {
public:
    // Constructor con función de callback para el click
    BotonRectangular(int x, int y, int w, int h, 
                    SDL_Color colorNormal, 
                    SDL_Color colorHover);
    
    void render(SDL_Renderer* renderer) const override;
    void handleEvents(const EventHandler& eventHandler);

private:
    SDL_Color colorNormal;
    SDL_Color colorHover;
    //std::function<void()> onClick;
};
