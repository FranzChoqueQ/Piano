#include "PianoKey.hpp"
#include <iostream>

PianoKey::PianoKey(int x, int y, int w, int h, SDL_Color color, KeyType keyType, int id)
    : Rectangle(x, y, w, h, color), type(keyType), noteID(id), active(false)
{}

void PianoKey::render(SDL_Renderer* renderer) const {
    /*std::cout << "🎹 Render -> ID=" << noteID 
          << " | Tipo=" << (type == KeyType::WHITE ? "Blanca" : "Negra") 
          << " | Pos: (" << rect.x << "," << rect.y 
          << ") Tamaño: " << rect.w << "x" << rect.h << std::endl;*/

    // Si está activa, le damos un brillo distinto
    SDL_Color drawColor = active
        ? SDL_Color{ Uint8(color.r / 2), Uint8(color.g / 2), Uint8(color.b / 2), color.a }
        : color;
    
    SDL_Delay(1); // Esta parte hay que eliminar para que suene multiples teclas pero hay que añadir un control de SDL_MIXER

    SDL_SetRenderDrawColor(renderer, drawColor.r, drawColor.g, drawColor.b, drawColor.a);
    SDL_RenderFillRect(renderer, &rect);

    // Opcional: contorno
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);
}

void PianoKey::setActive(bool isActive) {
    active = isActive;
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
