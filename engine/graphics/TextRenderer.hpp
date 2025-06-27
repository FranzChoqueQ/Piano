#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <memory>

class TextRenderer {
public:
    TextRenderer();
    ~TextRenderer();
    
    bool loadFont(const std::string& path, int fontSize);
    void render(SDL_Renderer* renderer, const std::string& text, int x, int y, SDL_Color color);
    void setFontSize(int size);
    
    // Métodos para obtener dimensiones del texto
    int getTextWidth(const std::string& text) const;
    int getTextHeight(const std::string& text) const;

private:
    TTF_Font* font;
    std::string fontPath;
    int currentSize;
    
    bool reloadFont();
};