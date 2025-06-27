#include "TecladoPiano.hpp"
#include <iostream>

TecladoPiano::TecladoPiano(int xOffset, int yOffset) {
    
    std::cout << "=== INICIALIZANDO TECLADO ===" << std::endl;
    std::cout << "Posicion base: X=" << xOffset << " Y=" << yOffset << std::endl;

    // 🎹 Dimensiones base
    const int whiteKeyWidth  = 32;    // 25 blancas = 800 px
    const int whiteKeyHeight = 200;
    const int blackKeyWidth  = 20;
    const int blackKeyHeight = 120;

    // 🎶 Patrones para teclas negras (0: no hay, 1: hay tecla negra entre blancas)
    const int blackKeyMap[25] = {
        1,1,0,1,1,1,0,1,1,0,1,1,1,0,1,1,0,1,1,1,0,1,1,0,0
        // Posiciones relativas donde hay tecla negra: C, C#, D, D#, E, F...
    };

    SDL_Color whiteColor = {255, 255, 255, 255};
    SDL_Color blackColor = {0, 0, 0, 255};

    int noteID = 0;

    // 🔲 Crear teclas blancas
    for (int i = 0; i < 25; ++i) {
        int x = xOffset + i * whiteKeyWidth;
        /*std::cout << "🟨 BLANCA: ID=" << noteID << " | x=" << x << " y=" << yOffset
                << " w=" << whiteKeyWidth << " h=" << whiteKeyHeight << std::endl;*/
        teclasBlancas.push_back(PianoKey(x, yOffset, whiteKeyWidth, whiteKeyHeight, whiteColor, KeyType::WHITE, noteID++));
    }

    // ⬛ Crear teclas negras
    for (int i = 0; i < 25; ++i) {
        if (blackKeyMap[i]) {
            int x = xOffset + (i * whiteKeyWidth) + (whiteKeyWidth - blackKeyWidth / 2);
            /*std::cout << "⬛ NEGRA: ID=" << noteID << " | x=" << x << " y=" << yOffset
                    << " w=" << blackKeyWidth << " h=" << blackKeyHeight << std::endl;*/
            teclasNegras.push_back(PianoKey(x, yOffset, blackKeyWidth, blackKeyHeight, blackColor, KeyType::BLACK, noteID++));
        }
    }
}

void TecladoPiano::render(SDL_Renderer* renderer) const {
    //std::cout << "\n=== RENDERIZANDO TECLADO ===" << std::endl;
    // ⚪ Dibujar teclas blancas primero
    for (const auto& key : teclasBlancas) {
        key.render(renderer);
    }

    // ⚫ Luego dibujar negras por encima
    for (const auto& key : teclasNegras) {
        key.render(renderer);
    }
}

void TecladoPiano::handleEvents(const EventHandler& e) {
    for (auto& key : teclasBlancas) {
        key.setActive(key.isClicked(e));
    }

    for (auto& key : teclasNegras) {
        key.setActive(key.isClicked(e));
    }
}

const PianoKey* TecladoPiano::getKeyAt(int x, int y) const {
    // 🖱️ Primero intentamos con las teclas negras (están encima)
    for (const auto& key : teclasNegras) {
        if (key.getRect().x <= x && x <= key.getRect().x + key.getRect().w &&
            key.getRect().y <= y && y <= key.getRect().y + key.getRect().h) {
            return &key;
        }
    }

    // Luego teclas blancas
    for (const auto& key : teclasBlancas) {
        if (key.getRect().x <= x && x <= key.getRect().x + key.getRect().w &&
            key.getRect().y <= y && y <= key.getRect().y + key.getRect().h) {
            return &key;
        }
    }
    return nullptr;
}
