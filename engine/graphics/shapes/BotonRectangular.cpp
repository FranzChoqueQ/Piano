#include "BotonRectangular.hpp"

BotonRectangular::BotonRectangular(int x, int y, int w, int h, 
                                 SDL_Color colorNormal, 
                                 SDL_Color colorHover)
    : Rectangle(x, y, w, h, colorNormal), 
      colorNormal(colorNormal),
      colorHover(colorHover) {}

void BotonRectangular::render(SDL_Renderer* renderer) const {
    // No necesitamos override realmente, pero lo dejamos por claridad
    Rectangle::render(renderer);
}

void BotonRectangular::handleEvents(const EventHandler& eventHandler) {
    if (isMouseOver(eventHandler)) {
        setColor(colorHover);
    } else {
        setColor(colorNormal);
    }
}