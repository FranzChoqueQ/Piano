#pragma once
#include <vector>
#include "PianoKey.hpp"
#include "EventHandler.hpp"
#include <SDL2/SDL_mixer.h>

class TecladoPiano {
    std::vector<PianoKey> teclasBlancas;
    std::vector<PianoKey> teclasNegras;

public:
    TecladoPiano(int xOffset = 0, int yOffset = 0);
    ~TecladoPiano();

    void update();
    
    void render(SDL_Renderer* renderer) const;
    void handleEvents(const EventHandler& event);
    
    const PianoKey* getKeyAt(int x, int y) const;

    void setOnlyKeyActive(int noteID);

    std::vector<Mix_Chunk*> sounds;
    Mix_Chunk* sound;
};
