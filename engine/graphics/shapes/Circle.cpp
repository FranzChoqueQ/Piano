#include "Circle.hpp"

Circle::Circle(int x, int y, int radio, SDL_Color color) : x(x), y(y), radio(radio), color(color) {

}

Circle::~Circle(){}

void Circle::render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    drawCircle(renderer, x, y);
}

void Circle::handleEvent(const EventHandler& event){

}

void Circle::setColor(SDL_Color newColor){

}

void Circle::setPosition(int new_x, int new_y){
    x = new_x;
    y = new_y;
}

void Circle::drawCircle(SDL_Renderer* renderer, int x_c, int y_c) const{
    int d = 3-2*radio;
    int xc2 = x_c;
    int yc2 = y_c - radio;
    while(x <= y){
        SDL_RenderDrawPoint(renderer, xc2, yc2);
        if(d < 0){
            d = d + 4*x + 6;
        }
        else{
            d = d + 4*(x-y) + 10;
            yc2--;
        }
        xc2++;
    }
}

/*
    Circle(int x, int y, int radio, SDL_Color color);
    virtual ~Circle();

    void render(SDL_Renderer* renderer) const;
    void handleEvent(const EventHandler& event);
    void setColor(SDL_Color newColor);
    void setPosition(int new_x, int new_y);*/
