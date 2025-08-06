#include "TecladoPiano.hpp"
#include <iostream>
#include <map>

//#include <SDL2/SDL_scancode.h> // si no lo tenés ya

TecladoPiano::TecladoPiano(int xOffset, int yOffset) {

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer error: " << Mix_GetError() << std::endl;
    }

    const std::string basePath = "assets/sounds/";
    const std::vector<std::string> noteFiles = {
        "F2.mp3", "Gb2.mp3", "G2.mp3", "Ab2.mp3", "A2.mp3", "Bb2.mp3", "B2.mp3",
        "C3.mp3", "Db3.mp3", "D3.mp3", "Eb3.mp3", "E3.mp3",
        "F3.mp3", "Gb3.mp3", "G3.mp3", "Ab3.mp3", "A3.mp3", "Bb3.mp3", "B3.mp3",
        "C4.mp3", "Db4.mp3", "D4.mp3", "Eb4.mp3", "E4.mp3",
        "F4.mp3", "Gb4.mp3", "G4.mp3", "Ab4.mp3", "A4.mp3", "Bb4.mp3", "B4.mp3",
        "C5.mp3", "Db5.mp3", "D5.mp3", "Eb5.mp3", "E5.mp3",
        "F5.mp3", "Gb5.mp3", "G5.mp3", "Ab5.mp3", "A5.mp3", "Bb5.mp3"
    };

    for (const auto& file : noteFiles) {
        Mix_Chunk* sound = Mix_LoadWAV((basePath + file).c_str());
        if (!sound) {
            std::cerr << "Error cargando: " << file << " → " << Mix_GetError() << std::endl;
        }
        sounds.push_back(sound);
    }

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

TecladoPiano::~TecladoPiano(){
    Mix_CloseAudio();
}

std::string getNoteNameFromOffset(int noteID) {
        const std::string names[12] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
        int midi = 41 + noteID; // 41 = F2
        return names[midi % 12] + std::to_string((midi / 12) - 1);
    }

void TecladoPiano::update(){
    for (auto& key : teclasBlancas) key.update();
    for (auto& key : teclasNegras) key.update();
}

void TecladoPiano::render(SDL_Renderer* renderer) const {
    //std::cout << "\n=== RENDERIZANDO TECLADO ===" << std::endl;
    // ⚪ Dibujar teclas blancas primero
    for (const auto& key : teclasBlancas) {
        key.renderPianoKey(renderer);
    }

    // ⚫ Luego dibujar negras por encima
    for (const auto& key : teclasNegras) {
        key.renderPianoKey(renderer);
    }
}

const std::map<SDL_Scancode, int> keyToNoteID = {
        { SDL_SCANCODE_1, 0 },  // F2
        { SDL_SCANCODE_2, 1 },  // F#2
        { SDL_SCANCODE_3, 2 },  // G2
        { SDL_SCANCODE_4, 3 },  // G#2
        { SDL_SCANCODE_5, 4 },  // A2
        { SDL_SCANCODE_6, 5 },  // A#2
        { SDL_SCANCODE_7, 6 },  // B2
        { SDL_SCANCODE_8, 7 },  // C3
        { SDL_SCANCODE_9, 8 },  // C#3
        { SDL_SCANCODE_0, 9 },  // D3
        { SDL_SCANCODE_APOSTROPHE, 10 }, // D#3
        { SDL_SCANCODE_SLASH, 11 }, // E3
        { SDL_SCANCODE_Q, 12 }, // F3
        { SDL_SCANCODE_W, 13 },  // F#3
        { SDL_SCANCODE_E, 14 },  // G3
        { SDL_SCANCODE_R, 15 },  // G#3
        { SDL_SCANCODE_T, 16 },  // A3
        { SDL_SCANCODE_Y, 17 },  // A#3
        { SDL_SCANCODE_U, 18 },  // B3
        { SDL_SCANCODE_I, 19 },  // C4
        { SDL_SCANCODE_O, 20 },  // C#4
        { SDL_SCANCODE_P, 21 },  // D4
        { SDL_SCANCODE_GRAVE, 22 },  // D#4
        { SDL_SCANCODE_A, 23 }, // E4
        { SDL_SCANCODE_S, 24 }, // F4
        { SDL_SCANCODE_D, 25 }, // F#4
        { SDL_SCANCODE_F, 26 },  // G4
        { SDL_SCANCODE_G, 27 },  // G#4
        { SDL_SCANCODE_H, 28 },  // A4
        { SDL_SCANCODE_J, 29 },  // A#4
        { SDL_SCANCODE_K, 30 },  // B4
        { SDL_SCANCODE_L, 31 },  // C5
        { SDL_SCANCODE_Z, 32 },  // C#5
        { SDL_SCANCODE_X, 33 },  // D5
        { SDL_SCANCODE_C, 34 },  // D#5
        { SDL_SCANCODE_V, 35 },  // E5
        { SDL_SCANCODE_B, 36 }, // F5
        { SDL_SCANCODE_N, 37 }, // F#5
        { SDL_SCANCODE_M, 38 }, // G5
        { SDL_SCANCODE_COMMA, 39 },  // G#5
        { SDL_SCANCODE_PERIOD, 40 },  // A5
        { SDL_SCANCODE_MINUS, 41 }  // A#5
    };

void loadSounds() {
    
}


void TecladoPiano::handleEvents(const EventHandler& event) {

    for (auto& key : teclasBlancas) {
        if (key.isClicked(event)) {
            key.setActive(true, true);
            std::cout << "🎵 Click sobre B: " << getNoteNameFromOffset(key.getNoteID()) << std::endl;
            int noteID = key.getNoteID();
            //Mix_PlayChannel(-1, sounds[noteID], 0);
            if (noteID >= 0 && noteID < sounds.size()) {
                Mix_PlayChannel(-1, sounds[noteID], 0);
            }
            return; // Tecla negra tiene prioridad visual
        }
    }

    for (auto& key : teclasNegras) {
        if (key.isClicked(event)) {
            key.setActive(true, false);
            std::cout << "🎵 Click sobre N: " << getNoteNameFromOffset(key.getNoteID()) << std::endl;
            int noteID = key.getNoteID();
            if (noteID >= 0 && noteID < sounds.size()) {
                Mix_PlayChannel(-1, sounds[noteID], 0);
            }
            return;
        }
    }

    // 🎹 Entrada desde teclado físico
    for (const auto& [scancode, noteID] : keyToNoteID) {
        //std::cout << "El resultado es: " << event.isKeyPressed(scancode) << std::endl;
        if (event.isKeyPressed(scancode)) {
            std::cout << "⌨️  Tecla fisica: " << getNoteNameFromOffset(noteID) << std::endl;
            Mix_PlayChannel(-1, sounds[noteID], 0);
            // Activar visualmente la tecla correspondiente
            for (auto& key : teclasBlancas){
                key.setActive(key.getNoteID() == noteID, true);
            }
        
            for (auto& key : teclasNegras){
                key.setActive(key.getNoteID() == noteID, false);
            }  
            return;
        }
    }
}

const PianoKey* TecladoPiano::getKeyAt(int x, int y) const {
    // Teclas negras encima
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

void TecladoPiano::setOnlyKeyActive(int noteID) {
    for (auto& key : teclasBlancas)
        key.setActive(key.getNoteID() == noteID, true);

    for (auto& key : teclasNegras)
        key.setActive(key.getNoteID() == noteID, false);
}