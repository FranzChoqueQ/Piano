#pragma once

#include <SDL2/SDL.h>

#include "engine/core/EventHandler.hpp"

class Rectangle{
public:
    Rectangle(int x, int y, int w, int h, SDL_Color color); //Esquina superior izquierda (x,y) h->height w-> width
    virtual ~Rectangle();

    //Metodos de renderizado
    virtual void render(SDL_Renderer* renderer) const;

    //Metodos de deteccion de interaccion
    bool isMouseOver(const EventHandler& event) const;
    bool isClicked(const EventHandler& event) const;

    // Metodo virtual para manejar eventos personalizados
    virtual void handleEvent(EventHandler& event);

    // Getter para el rectangulo por si lo necesitan clases derivadas
    SDL_Rect getRect() const;

    // Permite cambiar color o posicion
    void setColor(SDL_Color newColor);
    //void setPosition(int x, int y);

    SDL_Rect rect;
    SDL_Color color;

private:
          // Posición y tamaño
        // Color del rectangulo 
};

