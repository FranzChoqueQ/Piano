#include "PianoKey.hpp"
#include <iostream>

PianoKey::PianoKey(int x, int y, int w, int h, SDL_Color color, KeyType keyType, int id)
    : Rectangle(x, y, w, h, color), type(keyType), noteID(id), active(false), tBlanca(false), delay(0), originalColor(color)  // Guarda el color inicial al construir
{}

void PianoKey::update() {
    if (active) {
        delay++;
        std::cout << "Tecla " << noteID << " - Delay: " << delay 
                  << " - Active: " << active << std::endl;

        // Solo cambia el color si está activo
        setColor(type == KeyType::WHITE ? 
                SDL_Color{255, 200, 200, 255} : 
                SDL_Color{100, 100, 100, 255});

        if (delay >= 100) {
            std::cout << "Desactivando tecla " << noteID << std::endl;
            active = false;
            delay = 0;
            setColor(originalColor);  // Restaura color original
        }
    }
}

void PianoKey::renderPianoKey(SDL_Renderer* renderer) const{
    Rectangle::render(renderer);  // Dibuja el rectángulo base
    
    // Contorno
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);
}

void PianoKey::setActive(bool isActive, bool teclaBlanca) {
    if (isActive) {
        // Solo reinicia si no estaba ya activa
        if (!active) {
            delay = 0;
            originalColor = color;  // Guarda el color actual
        }
    }
    active = isActive;
    tBlanca = teclaBlanca;
    
    std::cout << "Tecla " << noteID << " setActive: " << isActive 
              << " (Estado actual: " << active << ")" << std::endl;
}

bool PianoKey::isActive() const {
    return active;
}

KeyType PianoKey::getType() const {
    return type;
}

int PianoKey::getNoteID() const {
    return noteID;
}
