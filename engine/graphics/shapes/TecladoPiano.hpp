#pragma once
#include <vector>
#include "PianoKey.hpp"
#include "EventHandler.hpp"

class TecladoPiano {
    std::vector<PianoKey> teclasBlancas;
    std::vector<PianoKey> teclasNegras;

public:
    TecladoPiano(int xOffset = 0, int yOffset = 0);
    
    void render(SDL_Renderer* renderer) const;
    void handleEvents(const EventHandler& e);
    
    const PianoKey* getKeyAt(int x, int y) const;
    TecladoPiano(const TecladoPiano&) = delete;
    TecladoPiano& operator=(const TecladoPiano&) = delete;
};
