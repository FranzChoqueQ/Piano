#pragma once
#include "Rectangle.hpp"

enum class KeyType { WHITE, BLACK };

class PianoKey : public Rectangle {
    KeyType type;
    int noteID;              // Índice MIDI o similar
    bool active;

public:
    PianoKey(int x, int y, int w, int h, SDL_Color color, KeyType type, int noteID);

    void render(SDL_Renderer* renderer) const override;
    void setActive(bool isActive);
    bool isActive() const;
    KeyType getType() const;
    int getNoteID() const;

    //SDL_Color color;
    //SDL_Rect rect;
};
