#include "Rectangle.hpp"

Rectangle::Rectangle(int x, int y, int w, int h, SDL_Color color) : rect{x,y,w,h}, color(color){
    
}

Rectangle::~Rectangle() {
    // Implementación vacía pero necesaria
}

void Rectangle::render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}

void Rectangle::handleEvent(EventHandler& event) {
    // Implementación base vacía o común para todos los rectángulos
}

bool Rectangle::isMouseOver(const EventHandler& event) const {
    int mx, my;
    event.getMousePosition(mx,my);
    return (mx >= rect.x && mx <= rect.x + rect.w && my >= rect.y && my <= rect.y + rect.h);
}

bool Rectangle::isClicked(const EventHandler& event) const {
    return isMouseOver(event) && event.isMouseButtonPressed(SDL_BUTTON_LEFT);
}

SDL_Rect Rectangle::getRect() const {
    return rect;
}

void Rectangle::setColor(SDL_Color newColor) {
    color = newColor;
}

/*
void Rectangle::setPosition(int x, int y) {
    rect.x = x;
    rect.y = y;
}*/

