#pragma once
#include "Rectangle.hpp"

enum class KeyType { WHITE, BLACK };

class PianoKey : public Rectangle {
private:
    KeyType type;
    int noteID;              // Índice MIDI o similar
    bool active;
    bool tBlanca;
    int delay;
    SDL_Color originalColor;

public:
    PianoKey(int x, int y, int w, int h, SDL_Color color, KeyType type, int noteID);

    void update();
    //void render(SDL_Renderer* renderer) const override;
    void renderPianoKey(SDL_Renderer* renderer) const;
    void setActive(bool isActive, bool teclaBlanca);
    bool isActive() const;
    KeyType getType() const;
    int getNoteID() const;
    using Rectangle::setColor;
};
